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
 * @file esp32_platform_task.c
 * @author Anna Sopdia Schröck
 * @date 3 Februar 20119
 * @brief all esp32 platform task functions source
 *
 */
#include "config.h"
#ifdef ESS_CONFIC_TASK_ESP32

#include "ess_backend.h"
#include "ess_platform.h"


#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#define LOG_TAG  "OesSpT"

static int task_id = 0;

ess_error_t ess_platform_sleep(unsigned int ms) {
  vTaskDelay(ms / portTICK_PERIOD_MS);
  return ESS_OK;
}
unsigned int ess_platform_get_tick_count() {
  return (uint32_t) (xTaskGetTickCount() * portTICK_PERIOD_MS);
}


ess_error_t ess_platform_task_create(ess_platform_task_t* task, void task_func(void*),
    const char* taskName, void* param, unsigned int stackSize) {
      if(task == 0) return ESS_ERROR_NULL;

      task->name[0] = '\0';
      strncpy(task->name, taskName, sizeof(task->name) );

      task->parem = param;
      task->stack_size = stackSize;
      task->task = task_func;
      task->userdata = param;
      task->task_id = task_id++;
      task->handle = 0;
      task->priority = 5;

      return ESS_OK;
}
ess_error_t ess_platform_task_start(ess_platform_task_t* task) {
  xTaskCreate(task->task, task->name, task->stack_size, task->userdata , task->priority,  task->handle);

  return ESS_OK;
}
ess_error_t ess_platform_task_delete(ess_platform_task_t* task) {
  if(task == 0) return ESS_ERROR_NULL;

  vTaskDelete(task->handle);

  return ESS_OK;
}
#endif
