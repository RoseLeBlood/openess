/****************************************************************************
 * Copyright (C) 2019 by Anna Sopdia Schröck                                *
 *                                                                          *
 * This file is part of ess.                                                *
 *                                                                          *
 *   ess is free software: you can redistribute it and/or modify it         *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   ess is distributed in the hope that it will be useful,                 *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Box.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/

/**
 * @file ess_audio_stream.h
 * @author Anna Sopdia Schröck
 * @date 03 März 2019
 * @brief audio stream
 *
 *
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


typedef struct ess_audio_block {
	uint8_t  count;
	uint8_t  ressv;
	uint16_t index;
  float    data[ESS_DEFAULT_AUDIO_PACKET_SIZE];
} ess_audio_block_t;

#define ess_audio_memory(num) ({ \
	static ess_audio_block_t data[num]; \
	ess_audio_stream::initialize_memory(data, num); \
})

#define ess_audio_memory_use() (ess_audio_stream::get_mem_used())
#define ess_audio_memory_use_max() (ess_audio_stream::get_mem_umax())
#define ess_audio_memory_use_max_reset() (ess_audio_stream::set_mem_umax(ess_audio_stream::get_mem_umax()))

class ess_audio_stream {
  friend class ess_audio_conections;
public:
  ess_audio_stream() { }

	ess_audio_stream(unsigned char ninput, ess_audio_block_t **iqueue, const std::string defaultName,
    ess_format_t format = ESS_DEFAULT_SERVER_FORMAT);

	bool is_active(void) { return m_bActive; }

  virtual ess_error_t update(void) = 0;

  static void update_all(ess_format_t format);
  static void initialize_memory(ess_audio_block_t *data, unsigned int num);

  uint32_t get_clocks_per_update() { return m_iClocksPerUpdate; }
  uint32_t get_clocks_per_seconds() { return m_iClocksPerSecond; }
  uint32_t get_clocks_per_update_min() { return m_iClocksPerUpdateMin; }
  uint32_t get_clocks_per_update_max() { return m_iClocksPerUpdateMax; }
  static uint16_t get_mem_used() { return m_uMemoryUsed; }
  static uint16_t get_mem_umax() { return m_uMemoryUsedMax; }

  void set_clocks_per_update(uint32_t value) { m_iClocksPerUpdate = value; }
  void set_clocks_per_seconds(uint32_t value) { m_iClocksPerSecond = value; }
  void set_clocks_per_update_min(uint32_t value) { m_iClocksPerUpdateMin = value; }
  void set_clocks_per_update_max(uint32_t value) { m_iClocksPerUpdateMax = value; }
  static void  set_mem_used(uint16_t value) { m_uMemoryUsed = value; }
  static void set_mem_umax(uint16_t value) { m_uMemoryUsedMax = value; }

protected:
	void transmit(ess_audio_block_t *block, unsigned char index = 0);
	ess_audio_block_t * receiveReadOnly(unsigned int index = 0);
	ess_audio_block_t * receiveWritable(unsigned int index = 0);

  static ess_audio_block_t * allocate(void);
	static void release(ess_audio_block_t * block);


protected:
  static ess_audio_stream *m_pFirstUpdate;
  static bool m_bBlockingObjectRun;

	std::string m_strName;
	ess_audio_stream *m_pNextUpdate;
	bool m_bActive;
	bool m_bBlocking;
	bool m_bInit;
	unsigned char m_ucNumInputs;
	uint8_t m_ucNumConn;

  static uint16_t m_uMemoryUsed;
	static uint16_t m_uMemoryUsedMax;

	uint32_t m_iClocksPerUpdate;
	uint32_t m_iClocksPerUpdateMax;
	uint32_t m_iClocksPerUpdateMin;
	uint32_t m_iClocksPerSecond;

	ess_format_t m_eFormat;
private:
  static ess_audio_block_t *m_pMemoryPool;
	static uint32_t m_pMemoryPoolAvbm[];
	static uint16_t m_pMemoryPoolFirst;



	ess_audio_conections *m_pDestList;
	ess_audio_block_t **m_pInputQueue;
	uint32_t m_uiClocksPerSecSum;

};

/**
* @}
*/

#endif
