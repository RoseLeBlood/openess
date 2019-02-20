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
 * @file esp32_platform_mutex.cpp
 * @author Anna Sopdia Schröck
 * @date 11 Februar 2019
 * @brief all esp32 platform mutex class source
 *
 */
#include "config.h"
#ifdef ESS_CONFIG_MUTEX_ESP32
#include "ess_platform.h"
#include "ess_mutex.h"
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include <stdio.h>

#include "esp_attr.h"

ess_mutex::ess_mutex() { }
ess_mutex::~ess_mutex() {

}

ess_error_t ess_mutex::create() {
  m_pHandle = xSemaphoreCreateBinary();
  return unlock();
}
ess_error_t ess_mutex::destroy() {
  if(m_pHandle == 0) return ESS_ERROR_NULL;
  vSemaphoreDelete(m_pHandle) ;
  return ESS_OK;
}
ess_error_t ess_mutex::lock() {
  if(m_pHandle == 0) return ESS_ERROR_NULL;

  if (xPortInIsrContext()) {
       BaseType_t xHigherPriorityTaskWoken = pdFALSE;
       xSemaphoreTakeFromISR( m_pHandle, &xHigherPriorityTaskWoken );
       if(xHigherPriorityTaskWoken)
         _frxt_setup_switch();
   } else {
    xSemaphoreTake(m_pHandle, portMAX_DELAY);
   }

  return ESS_OK;
}
ess_error_t ess_mutex::unlock() {
  if(m_pHandle == 0) return ESS_ERROR_NULL;

  if (xPortInIsrContext()) {
       BaseType_t xHigherPriorityTaskWoken = pdFALSE;
       xSemaphoreGiveFromISR( m_pHandle, &xHigherPriorityTaskWoken );
       if(xHigherPriorityTaskWoken)
         _frxt_setup_switch();
   } else {
      xSemaphoreGive(m_pHandle);
  }
  return ESS_OK;
}

ess_error_t ess_mutex::try_lock() {
  if(m_pHandle == 0) return ESS_ERROR_NULL;

  return (xSemaphoreTake( m_pHandle, 0 ) == pdTRUE) ? ESS_OK : ESS_ERROR;
}
#endif
