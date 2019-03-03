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

class ess_audio_stream {
  friend class ess_audio_conections;
public:
	ess_audio_stream(unsigned char ninput, ess_audio_block_t **iqueue, const std::string defaultName);

	bool is_active(void) { return active; }

  static void update_all(void);
  static void initialize_memory(ess_audio_block_t *data, unsigned int num);

  uint32_t get_clocks_per_update() { return clocksPerUpdate; }
  uint32_t get_clocks_per_seconds() { return clocksPerSecond; }
  uint32_t get_clocks_per_update_min() { return clocksPerUpdateMin; }
  uint32_t get_clocks_per_update_max() { return clocksPerUpdateMax; }
  static uint16_t get_mem_used() { return memory_used; }
  static uint16_t get_mem_umax() { return memory_used_max; }

  void set_clocks_per_update(uint32_t value) { clocksPerUpdate = value; }
  void set_clocks_per_seconds(uint32_t value) { clocksPerSecond = value; }
  void set_clocks_per_update_min(uint32_t value) { clocksPerUpdateMin = value; }
  void set_clocks_per_update_max(uint32_t value) { clocksPerUpdateMax = value; }
  static void  set_mem_used(uint16_t value) { memory_used = value; }
  static void set_mem_umax(uint16_t value) { memory_used_max = value; }

protected:
	void transmit(ess_audio_block_t *block, unsigned char index = 0);
	ess_audio_block_t * receiveReadOnly(unsigned int index = 0);
	ess_audio_block_t * receiveWritable(unsigned int index = 0);

  static ess_audio_block_t * allocate(void);
	static void release(ess_audio_block_t * block);
protected:
  static ess_audio_stream *first_update;
  static bool blockingObjectRunning;

	std::string name;
	ess_audio_stream *next_update;
	bool active;
	bool blocking;
	bool initialised;
	unsigned char num_inputs;
	uint8_t numConnections;

  static uint16_t memory_used;
	static uint16_t memory_used_max;

	uint32_t clocksPerUpdate;
	uint32_t clocksPerUpdateMax;
	uint32_t clocksPerUpdateMin;
	uint32_t clocksPerSecond;
private:
  static ess_audio_block_t *memory_pool;
	static uint32_t memory_pool_available_mask[];
	static uint16_t memory_pool_first_mask;

  virtual void update(void) = 0;

	ess_audio_conections *destination_list;
	ess_audio_block_t **inputQueue;
	uint32_t clocksPerSecondSum;
};

/**
* @}
*/

#endif
