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
 * @file esp32_platform_ringbffer.c
 * @author Anna Sopdia Schröck
 * @date 3 Februar 20119
 * @brief all esp32 platform ringbuffer functions source
 *
 */
#include "config.h"
#ifdef ESS_CONFIG_RINGBUFFER_ESP32

#include "ess_backend.h"
#include "ess_platform.h"
#include "ess_ringbuffer.h"

#include <stdio.h>
#include <string.h>

#include  <freertos/FreeRTOS.h>   // Include the base FreeRTOS definitions
#include "freertos/queue.h"
#include "freertos/ringbuf.h"

#include "esp_log.h"
#define LOG_TAG  "OesSpR"

ess_error_t ess_platform_ringbuffer_create(ess_platform_ringbuffer_t* rng,
  unsigned int length,  ess_platform_ringbuffer_mode_t type, const char* name) {
  if(rng == 0) return ESS_ERROR_NULL;
  strncpy(rng->name, name, sizeof(rng->name) );

  rng->type = type;

  if(type == ESS_PLATFORM_RINGBUFFER_MODE_NOSPLIT)
    rng->handle = xRingbufferCreate(length, RINGBUF_TYPE_NOSPLIT);
  else if(type == ESS_PLATFORM_RINGBUFFER_MODE_ALLOWSPLIT)
    rng->handle = xRingbufferCreate(length, RINGBUF_TYPE_ALLOWSPLIT);
  else
    rng->handle = xRingbufferCreate(length, RINGBUF_TYPE_BYTEBUF);

  rng->qhandle = xQueueCreateSet(3);
  if (xRingbufferAddToQueueSetRead(rng->handle, rng->qhandle) != pdTRUE) {
      printf("Failed to add to queue set\n");
      return ESS_ERROR;
  }

  return rng->handle == 0 ? ESS_OK : ESS_ERROR;
}
ess_error_t ess_platform_ringbuffer_write(ess_platform_ringbuffer_t* rng,
    void* data, unsigned int length, unsigned int ms) {
      if(rng == 0) return ESS_ERROR_NULL;

    return ( xRingbufferSend(rng->handle, data, length, pdMS_TO_TICKS(ms)) == pdTRUE ) ?
      ESS_OK :  ESS_ERROR;
}
void* ess_platform_ringbuffer_read(ess_platform_ringbuffer_t* rng, unsigned int* length, unsigned int ms) {
    if(rng == 0) return 0;

    return xRingbufferReceive(rng->handle, length, pdMS_TO_TICKS(ms));
}
ess_error_t ess_platform_ringbuffer_can_read(ess_platform_ringbuffer_t* rng, unsigned int ms) {
  if(rng == 0) return ESS_ERROR_NULL;

  xQueueSetMemberHandle member = xQueueSelectFromSet(rng->qhandle, pdMS_TO_TICKS(ms));

  return (member != NULL && xRingbufferCanRead(rng->handle, member) == pdTRUE) ?
    ESS_OK :  ESS_ERROR;
}
#endif
