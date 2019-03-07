
 /* Teensyduino Core Library
  * http://www.pjrc.com/teensy/
  * Copyright (c) 2017 PJRC.COM, LLC.
  *
  * Permission is hereby granted, free of charge, to any person obtaining
  * a copy of this software and associated documentation files (the
  * "Software"), to deal in the Software without restriction, including
  * without limitation the rights to use, copy, modify, merge, publish,
  * distribute, sublicense, and/or sell copies of the Software, and to
  * permit persons to whom the Software is furnished to do so, subject to
  * the following conditions:
  *
  * 1. The above copyright notice and this permission notice shall be
  * included in all copies or substantial portions of the Software.
  *
  * 2. If the Software is incorporated into a build system that allows
  * selection among a list of target devices, then similar target
  * devices manufactured by PJRC.COM must be included in the list of
  * target devices and selectable in the same manner.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
  * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
  * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  * SOFTWARE.
  */

#include "ess_audio_stream.h"
#include "ess_task.h"
#include "ess_platform.h"

# include <iostream>
# include <string>
# include <string.h>
# include <memory>
#include <sstream>

#define MAX_AUDIO_MEMORY 163840
#define NUM_MASKS  (((MAX_AUDIO_MEMORY / ESS_DEFAULT_AUDIO_PACKET_SIZE / 2) + 31) / 32)

class ess_audio_stream_mem {
public:
  static ess_audio_block_t * allocate(void);
	static void release(ess_audio_block_t * block);

  static uint16_t get_mem_used() { return m_uMemoryUsed; }
  static uint16_t get_mem_umax() { return m_uMemoryUsedMax; }

  static void initialize_memory(ess_audio_block_t *data, unsigned int num);
private:
  static ess_audio_block_t *m_pMemoryPool;
	static uint32_t m_pMemoryPoolAvbm[];
	static uint16_t m_pMemoryPoolFirst;
  static uint16_t m_uMemoryUsed;
	static uint16_t m_uMemoryUsedMax;
};
ess_audio_block_t * ess_audio_stream_mem::m_pMemoryPool;
uint32_t ess_audio_stream_mem::m_pMemoryPoolAvbm[NUM_MASKS];
uint16_t ess_audio_stream_mem::m_pMemoryPoolFirst;

uint16_t ess_audio_stream_mem::m_uMemoryUsed = 0;
uint16_t ess_audio_stream_mem::m_uMemoryUsedMax = 0;

void ess_audio_stream_mem::initialize_memory(ess_audio_block_t *data, unsigned int num)  {
	unsigned int i;
	unsigned int maxnum = MAX_AUDIO_MEMORY / ESS_DEFAULT_AUDIO_PACKET_SIZE / 2;

	if (num > maxnum) num = maxnum;

	m_pMemoryPool = data;
	m_pMemoryPoolFirst = 0;
	for (i=0; i < NUM_MASKS; i++) {
		m_pMemoryPoolAvbm[i] = 0;
	}
	for (i=0; i < num; i++) {
		m_pMemoryPoolAvbm[i >> 5] |= (1 << (i & 0x1F));
	}
	for (i=0; i < num; i++) {
		data[i].index = i;
	}
}

ess_audio_block_t * ess_audio_stream_mem::allocate(void)
{
	uint32_t n, index, avail;
	uint32_t *p, *end;
	ess_audio_block_t *block;
	uint32_t used;

	p = m_pMemoryPoolAvbm;
	end = p + NUM_MASKS;
	index = m_pMemoryPoolFirst;
	p += index;

	while (1) {
		if (p >= end) {
			return NULL;
		}
		avail = *p;
		if (avail) break;
		index++;
		p++;
	}

	n = __builtin_clz(avail);
	avail &= ~(0x80000000 >> n);
	*p = avail;

	if (!avail)
    index++;

	m_pMemoryPoolFirst = index;
	used = m_uMemoryUsed + 1;
	m_uMemoryUsed = used;

	index = p - m_pMemoryPoolAvbm;
	block = m_pMemoryPool + ((index << 5) + (31 - n));
	block->count = 1;

	if (used > m_uMemoryUsedMax)
    m_uMemoryUsedMax = used;

	return block;
}


void ess_audio_stream_mem::release(ess_audio_block_t *block) {
	uint32_t mask = (0x80000000 >> (31 - (block->index & 0x1F)));
	uint32_t index = block->index >> 5;

	if (block->count > 1) {
		block->count--;
	} else {
		m_pMemoryPoolAvbm[index] |= mask;
		if (index < m_pMemoryPoolFirst) m_pMemoryPoolFirst = index;
		  m_uMemoryUsed--;
	}
}

/* ****************************************************************** */


bool ess_audio_stream::m_bBlockingObjectRun = false;


ess_audio_stream::ess_audio_stream(unsigned char ninput, ess_audio_block_t **iqueue,
  const std::string defaultName, ess_format_t format) : m_strName(defaultName), m_ucNumInputs(ninput), m_pInputQueue(iqueue) {
  m_bActive = false;
  m_bBlocking = false;
  m_pDestList = NULL;
  m_eFormat = format;

  for (int i=0; i < m_ucNumInputs; i++) {
    m_pInputQueue[i] = NULL;
  }
  m_pNextUpdate = NULL;
  m_ucNumConn = 0;
}

ess_audio_block_t * ess_audio_stream::allocate(void) {
    return ess_audio_stream_mem::allocate();
}

void ess_audio_stream::release(ess_audio_block_t * block) {
  ess_audio_stream_mem::release(block);
}
void ess_audio_stream::transmit(ess_audio_block_t *block, unsigned char index) {
	for (ess_audio_conections *c = m_pDestList; c != NULL; c = c->m_pNext) {
		if (c->m_iSrcIndex == index) {
			if (c->m_pDst.m_pInputQueue[c->m_iDestIndex] == NULL) {
				c->m_pDst.m_pInputQueue[c->m_iDestIndex] = block;
				block->count++;
			}
		}
	}
}

ess_audio_block_t * ess_audio_stream::receive_read_only(unsigned int index) {
	ess_audio_block_t *in;

	if (index >= m_ucNumInputs) return NULL;
	in = m_pInputQueue[index];
	m_pInputQueue[index] = NULL;
	return in;
}

ess_audio_block_t * ess_audio_stream::receive_writable(unsigned int index) {
	ess_audio_block_t *in, *p;

	if (index >= m_ucNumInputs) return NULL;
	in = m_pInputQueue[index];
	m_pInputQueue[index] = NULL;
	if (in && in->count > 1) {
		p = allocate();
		if (p) memcpy(p->data, in->data, sizeof(p->data));
		in->count--;
		in = p;
	}
	return in;
}

std::string ess_audio_stream::get_info() {
  std::ostringstream temp;

  temp << get_name() << ":" << ( (get_type() == ESS_OUTPUT_STREAM)  ? "out": "in" )<<  ":"
    <<  ess_format_to_string(ESS_DEFAULT_SERVER_FORMAT) << ":" << get_blksize() << ":"
    << ( (is_used()) ? "used" : "not used" );

  return temp.str();
}
