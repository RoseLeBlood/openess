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
 * @file esp32_platform_semaphore.c
 * @author Anna Sopdia Schröck
 * @date 3 Februar 20119
 * @brief all esp32 platform semaphore functions source
 *
 */
#include "config.h"
#ifdef ESS_CONFIG_SEMAPHORE_ESP32

#include "ess_backend.h"
#include "ess_platform.h"


#include <stdio.h>
#include <string.h>

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#include "esp_log.h"
#define LOG_TAG  "OesSpS"

ess_platform_error_t ess_platform_semaphore_create(ess_platform_semaphore_t* semp, const char* name) {
  if(semp == 0) return ESS_PLATFORM_ERROR_NULL;
  strncpy(semp->name, name, sizeof(semp->name) );
  semp->handle = xSemaphoreCreateMutex();

  return semp->handle != 0 ?  ESS_PLATFORM_ERROR_OK : ESS_PLATFORM_ERROR ;
}
ess_platform_error_t ess_platform_semaphore_destroy(ess_platform_semaphore_t* semp) {
  if(semp == 0) return ESS_PLATFORM_ERROR_NULL;
  if(semp->handle == 0) return ESS_PLATFORM_NOT_CREATED;

   vSemaphoreDelete(semp->handle) ;
   return ESS_PLATFORM_ERROR_OK;
}
ess_platform_error_t ess_platform_semaphore_give_ex(ess_platform_semaphore_t* semp, int value) {
  if(semp == 0) return ESS_PLATFORM_ERROR_NULL;
  if(semp->handle == 0) return ESS_PLATFORM_NOT_CREATED;
  semp->value = value;
  return xSemaphoreGive(semp->handle)  == pdTRUE ?
    ESS_PLATFORM_ERROR_OK : ESS_PLATFORM_ERROR;
}
ess_platform_error_t ess_platform_semaphore_give(ess_platform_semaphore_t* semp) {
  if(semp == 0) return ESS_PLATFORM_ERROR_NULL;
  if(semp->handle == 0) return ESS_PLATFORM_NOT_CREATED;

  return xSemaphoreGive(semp->handle)  == pdTRUE ?
    ESS_PLATFORM_ERROR_OK : ESS_PLATFORM_ERROR;
}
ess_platform_error_t ess_platform_semaphore_give_isr(ess_platform_semaphore_t* semp) {
  if(semp == 0) return ESS_PLATFORM_ERROR_NULL;
  if(semp->handle == 0) return ESS_PLATFORM_NOT_CREATED;

  BaseType_t higherPriorityTaskWoken;
  return xSemaphoreGiveFromISR(semp->handle, &higherPriorityTaskWoken)  == pdTRUE ?
    ESS_PLATFORM_ERROR_OK : ESS_PLATFORM_ERROR;
}
ess_platform_error_t  ess_platform_semaphore_take_ex(ess_platform_semaphore_t* semp,  unsigned int timeout_ms) {

  if(semp == 0) return ESS_PLATFORM_ERROR_NULL;
  if(semp->handle == 0) return ESS_PLATFORM_NOT_CREATED;

  return xSemaphoreTake(semp->handle, timeout_ms / portTICK_PERIOD_MS)  == pdTRUE ?
    ESS_PLATFORM_ERROR_OK : ESS_PLATFORM_ERROR;
}
ess_platform_error_t ess_platform_semaphore_take(ess_platform_semaphore_t* semp) {

  if(semp == 0) return ESS_PLATFORM_ERROR_NULL;
  if(semp->handle == 0) return ESS_PLATFORM_NOT_CREATED;

  return xSemaphoreTake(semp->handle, portMAX_DELAY)  == pdTRUE ?
    ESS_PLATFORM_ERROR_OK : ESS_PLATFORM_ERROR;
}


ess_platform_error_t ess_platform_semaphore_wait(ess_platform_semaphore_t* semp, int* value) {
  if(semp == 0) return ESS_PLATFORM_ERROR_NULL;
  if(semp->handle == 0) return ESS_PLATFORM_NOT_CREATED;

  if(ess_platform_semaphore_take(semp) == ESS_PLATFORM_ERROR)
    return ESS_PLATFORM_ERROR;

  if(ess_platform_semaphore_give(semp) == ESS_PLATFORM_ERROR)
    return ESS_PLATFORM_ERROR;

  if(value) *value = semp->value;
  return ESS_PLATFORM_ERROR_OK;
}
#endif
