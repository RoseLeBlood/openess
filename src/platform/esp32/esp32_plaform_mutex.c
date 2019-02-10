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
 * @file esp32_platform_mutex.c
 * @author Anna Sopdia Schröck
 * @date 11 Februar 20119
 * @brief all esp32 platform ringbuffer functions source
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


ess_error_t ess_platform_mutex_create(ess_platform_mutex_t* mtx, const char* name) {
  if(mtx == 0) return ESS_ERROR_NULL;

  strncpy(mtx->name, name, 16);
  mtx->handle = xSemaphoreCreateBinary();

 return  ess_platform_mutex_unlock(mtx);
}
ess_error_t ess_platform_mutex_destroy(ess_platform_mutex_t* mtx) {
  if(mtx == 0) return ESS_ERROR_NULL;
  if(mtx->handle == 0) return ESS_ERROR_NULL;

  vSemaphoreDelete(mtx->handle) ;
  return ESS_OK;
}
ess_error_t ess_platform_mutex_lock(ess_platform_mutex_t* mtx) {
  if(mtx == 0) return ESS_ERROR_NULL;
  if(mtx->handle == 0) return ESS_ERROR_NULL;

  if (xPortInIsrContext()) {
       BaseType_t xHigherPriorityTaskWoken = pdFALSE;
       xSemaphoreTakeFromISR( mtx->handle, &xHigherPriorityTaskWoken );
       if(xHigherPriorityTaskWoken)
         _frxt_setup_switch();
   } else {
    xSemaphoreTake(mtx->handle, portMAX_DELAY);
   }

  return ESS_OK;
}
ess_error_t ess_platform_mutex_unlock(ess_platform_mutex_t* mtx) {
  if(mtx == 0) return ESS_ERROR_NULL;
  if(mtx->handle == 0) return ESS_ERROR_NULL;

  if (xPortInIsrContext()) {
       BaseType_t xHigherPriorityTaskWoken = pdFALSE;
       xSemaphoreGiveFromISR( mtx->handle, &xHigherPriorityTaskWoken );
       if(xHigherPriorityTaskWoken)
         _frxt_setup_switch();
   } else {
      xSemaphoreGive(mtx->handle);
  }
  return ESS_OK;
}

ess_error_t ess_platform_mutex_try_lock(ess_platform_mutex_t* mtx) {
  if(mtx == 0) return ESS_ERROR_NULL;
  if(mtx->handle == 0) return ESS_ERROR_NULL;

  return (xSemaphoreTake( mtx->handle, 0 ) == pdTRUE) ? ESS_OK : ESS_ERROR;
}
#endif
