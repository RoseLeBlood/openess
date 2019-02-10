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
 * @file esp32_platform_spinlock.c
 * @author Anna Sopdia Schröck
 * @date 11 Februar 20119
 * @brief all esp32 platform spinlock functions source
 *
 */
#include "config.h"
#ifdef ESS_CONFIG_SPINLOCK_ESP32
#include "ess_platform.h"
#include "ess_spinlock.h"
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include <stdio.h>

#include "esp_attr.h"


ess_error_t ess_platform_spinlock_create(ess_platform_spinlock_t* spi, const char* name,  int count) {
  if(spi == 0) return ESS_ERROR_NULL;

  strncpy(spi->name, name, 16);
  spi->handle = xSemaphoreCreateCounting(0x7fffffff, count);
  spi->handle = count;

 return  ess_platform_spinlock_unlock(spi);
}
ess_error_t ess_platform_spinlock_destroy(ess_platform_spinlock_t* spi) {
  if(spi == 0) return ESS_ERROR_NULL;
  if(spi->handle == 0) return ESS_ERROR_NULL;

  vSemaphoreDelete(spi->handle) ;
  return ESS_OK;
}
ess_error_t ess_platform_spinlock_lock(ess_platform_spinlock_t* spi) {
  if(spi == 0) return ESS_ERROR_NULL;
  if(spi->handle == 0) return ESS_ERROR_NULL;

  if (xPortInIsrContext()) {
       BaseType_t xHigherPriorityTaskWoken = pdFALSE;
       xSemaphoreTakeFromISR( spi->handle, &xHigherPriorityTaskWoken );
       if(xHigherPriorityTaskWoken)
         _frxt_setup_switch();
   } else {
    xSemaphoreTake(spi->handle, portMAX_DELAY);
   }

  return ESS_OK;
}
ess_error_t ess_platform_spinlock_unlock(ess_platform_spinlock_t* spi) {
  if(spi == 0) return ESS_ERROR_NULL;
  if(spi->handle == 0) return ESS_ERROR_NULL;

  if (xPortInIsrContext()) {
       BaseType_t xHigherPriorityTaskWoken = pdFALSE;
       xSemaphoreGiveFromISR( spi->handle, &xHigherPriorityTaskWoken );
       if(xHigherPriorityTaskWoken)
         _frxt_setup_switch();
   } else {
      xSemaphoreGive(spi->handle);
  }
  return ESS_OK;
}
ess_error_t ess_platform_spinlock_try_lock(ess_platform_spinlock_t* spi) {
  if(spi == 0) return ESS_ERROR_NULL;
  if(spi->handle == 0) return ESS_ERROR_NULL;

  return (xSemaphoreTake( spi->handle, 0 ) == pdTRUE) ? ESS_OK : ESS_ERROR;
}
#endif
