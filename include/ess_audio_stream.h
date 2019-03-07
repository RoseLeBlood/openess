
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

/**
 * @file ess_audio_stream.h
 * @author Anna Sopdia Schröck
 * @date 03 März 2019
 * @brief audio stream
 *
 * Rename AudioStream to ess_audio_stream
 */
 /**
 * @addtogroup stream
 * @{
 */
#ifndef __ESS_AUDIO_STREAM_H__
#define __ESS_AUDIO_STREAM_H__

#include <stdio.h>  // for NULL
#include <string.h> // for memcpy
#include <inttypes.h>

#include "ess.h"
#include "ess_audio_conections.h"
#include "ess_format.h"
#include "ess_mutex.h"
#include "ess_task.h"


typedef enum ess_stream_type {
  ESS_INPUT_STREAM,
  ESS_OUTPUT_STREAM
}ess_stream_type_t;


typedef struct ess_audio_block {
	uint8_t  count;
	uint8_t  ressv;
	uint16_t index;
  float    data[ESS_DEFAULT_AUDIO_PACKET_SIZE];
} ess_audio_block_t;

class ess_audio_stream {
  friend class ess_audio_conections;
	friend class ess_audio_system;
public:
  ess_audio_stream() { }

	ess_audio_stream(unsigned char ninput, ess_audio_block_t **iqueue, const std::string defaultName,
    ess_format_t format = ESS_DEFAULT_SERVER_FORMAT);


  virtual ess_error_t update(void) { return ESS_OK; }

  virtual ess_error_t probe(ess_format_t format) { return ESS_ERROR; }

  virtual ess_error_t open() {m_bActive = true;  return ESS_OK; }
  virtual ess_error_t close() {m_bActive = false;  return ESS_OK; }


  virtual bool 												is_used() { return m_bActive; }
	bool 																	 is_active(void) { return m_bActive; }

  virtual int 													get_blksize() { return ESS_DEFAULT_AUDIO_PACKET_SIZE ; }
  virtual ess_stream_type_t	 get_type() { return ESS_OUTPUT_STREAM; }
	virtual std::string 							get_info();
	virtual std::string						 		get_name() { return m_strName; }


	virtual void 												set_name(const std::string& value) { m_strName = value; }
protected:
	void transmit(ess_audio_block_t *block, unsigned char index = 0);
	ess_audio_block_t * receive_read_only(unsigned int index = 0);
	ess_audio_block_t * receive_writable(unsigned int index = 0);

  ess_audio_block_t * allocate(void);
	void release(ess_audio_block_t * block);
protected:
  static bool m_bBlockingObjectRun;

	std::string m_strName;
	ess_audio_stream *m_pNextUpdate;
	bool m_bActive;
	bool m_bBlocking;
	bool m_bInit;
	unsigned char m_ucNumInputs;
	uint8_t m_ucNumConn;

	ess_format_t m_eFormat;
private:
	ess_audio_conections *m_pDestList;
	ess_audio_block_t **m_pInputQueue;
};

/**
* @}
*/

#endif
