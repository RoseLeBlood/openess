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
 * @file esp32_platform_ringbffer.cpp
 * @author Anna Sopdia Schröck
 * @date 3 Februar 2019
 * @brief all esp32 platform ringbuffer functions source
 *
 */
#include "config.h"
#ifdef ESS_CONFIG_RINGBUFFER_ESP32

#include "ess_platform.h"
#include "ess_ringbuffer.h"

#include <stdio.h>
#include <string.h>

#include  <freertos/FreeRTOS.h>   // Include the base FreeRTOS definitions
#include "freertos/queue.h"
#include "freertos/ringbuf.h"

#include "esp_log.h"
#define LOG_TAG  "OesSpR"

ess_ringbuffer::ess_ringbuffer() {
}
ess_error_t ess_ringbuffer::create(unsigned int length,  ess_platform_ringbuffer_mode_t type) {
  m_tType = type;
  m_sLength = length;

  if(m_tType == ESS_PLATFORM_RINGBUFFER_MODE_NOSPLIT)
    m_pHandle = xRingbufferCreate(m_sLength, RINGBUF_TYPE_NOSPLIT);
  else if(m_tType == ESS_PLATFORM_RINGBUFFER_MODE_ALLOWSPLIT)
    m_pHandle = xRingbufferCreate(m_sLength, RINGBUF_TYPE_ALLOWSPLIT);
  else
    m_pHandle = xRingbufferCreate(m_sLength, RINGBUF_TYPE_BYTEBUF);

  m_pQHandle = xQueueCreateSet(3);
  if (xRingbufferAddToQueueSetRead(m_pHandle, m_pQHandle) != pdTRUE) {
      printf("Failed to add to queue set\n");
      return ESS_ERROR;
  }

  return m_pHandle == 0 ? ESS_OK : ESS_ERROR;
}
ess_error_t ess_ringbuffer::write(void* data, unsigned int length, unsigned int ms) {
  if(m_pHandle == 0) return ESS_ERROR_NULL;
  return ( xRingbufferSend(m_pHandle, data, length, pdMS_TO_TICKS(ms)) == pdTRUE ) ?
    ESS_OK :  ESS_ERROR;
}
void* ess_ringbuffer::read(unsigned int* length, unsigned int ms) {
    if(m_pHandle == 0) return 0;

    return xRingbufferReceive(m_pHandle, length, pdMS_TO_TICKS(ms));
}
ess_error_t ess_ringbuffer::can_read(unsigned int ms) {
  if(m_pHandle == 0) return ESS_ERROR_NULL;

  xQueueSetMemberHandle member = xQueueSelectFromSet(m_pQHandle, pdMS_TO_TICKS(ms));

  return (member != NULL && xRingbufferCanRead(m_pHandle, member) == pdTRUE) ?
    ESS_OK :  ESS_ERROR;
}
#endif
