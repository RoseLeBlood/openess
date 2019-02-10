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
#include "ess_task.h"

#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#define LOG_TAG  "OesSpT"

static int task_id = 0;



void thread_stub_esp32_platform_task(void* data);

ess_error_t ess_platform_task_create(ess_platform_task_t* task, void task_func(void*),
    const char* taskName, void* param, unsigned int stackSize) {
    if(task == 0) return ESS_ERROR_NULL;

    task->name[0] = '\0';
    strncpy(task->name, taskName, sizeof(task->name) );

    task->parem = param;
    task->stack_size = stackSize;

    task->userdata = param;
    task->task_id = task_id++;
    task->handle = 0;
    task->priority = 5;
    task->running = 0;

    if(ess_platform_mutex_create(&task->runningMutex, task->name) != ESS_OK)
      return ESS_ERROR_TASK_CREAT;
    if(ess_platform_mutex_create(&task->continuemutex, task->name) != ESS_OK)
      return ESS_ERROR_TASK_CREAT;
    if(ess_platform_mutex_create(&task->continuemutex2, task->name) != ESS_OK)
      return ESS_ERROR_TASK_CREAT;
    if(ess_platform_mutex_create(&task->contextMutext, task->name) != ESS_OK)
      return ESS_ERROR_TASK_CREAT;

      return ESS_OK;
}
ess_error_t ess_platform_task_start(ess_platform_task_t* task) {
  if(task == 0) return ESS_ERROR_NULL;

  ess_platform_mutex_lock(&task->continuemutex);
  ess_platform_mutex_lock(&task->runningMutex);

  if (task->running) {
    ess_platform_mutex_unlock(&task->continuemutex);
    ess_platform_mutex_unlock(&task->runningMutex);
    return ESS_OK;
  }
  ess_platform_mutex_unlock(&task->runningMutex);

  xTaskCreate( &thread_stub_esp32_platform_task,
    task->name, task->stack_size, task , task->priority,  task->handle);

	if (task->handle == 0) {
    ess_platform_mutex_unlock(&task->continuemutex);
		return ESS_ERROR;
  }

	ess_platform_mutex_unlock(&task->continuemutex);

  return ESS_OK;
}
ess_error_t ess_platform_task_delete(ess_platform_task_t* task) {
  if(task == 0) return ESS_ERROR_NULL;

  ess_platform_mutex_lock(&task->continuemutex);
  ess_platform_mutex_lock(&task->runningMutex);

  if (!task->running) {
    ess_platform_mutex_unlock(&task->continuemutex);
    ess_platform_mutex_unlock(&task->runningMutex);
    return ESS_OK;
  }

  vTaskDelete(task->handle); task->handle = 0;
  task->running = 0;

  ess_platform_mutex_unlock(&task->continuemutex);
  ess_platform_mutex_unlock(&task->runningMutex);

  return ESS_OK;
}
ess_error_t ess_platform_task_suspend(ess_platform_task_t* task) {
  if(task == 0) return ESS_ERROR_NULL;

  ess_platform_mutex_lock(&task->runningMutex);
  vTaskSuspend( task->handle );
  ess_platform_mutex_unlock(&task->runningMutex);
  return ESS_OK;
}
ess_error_t ess_platform_task_resume(ess_platform_task_t* task) {
  if(task == 0) return ESS_ERROR_NULL;

  ess_platform_mutex_lock(&task->runningMutex);
  vTaskResume( task->handle );
  ess_platform_mutex_unlock(&task->runningMutex);

  return ESS_OK;
}
void thread_stub_esp32_platform_task(void* data) {
  struct ess_platform_task *task;

	task = (struct ess_platform_task*)(data);

  ess_platform_mutex_lock(&task->continuemutex2);

  ess_platform_mutex_lock(&task->runningMutex);
  task->running = 1;
  ess_platform_mutex_unlock(&task->runningMutex);

  ess_platform_mutex_lock(&task->continuemutex);
  ess_platform_mutex_unlock(&task->continuemutex);

  ess_platform_mutex_unlock(&task->continuemutex2);
  task->task_stub(task->userdata);


  ess_platform_mutex_lock(&task->runningMutex);
  task->running = 0;

  vTaskDelete(task->handle);
  task->handle = 0;

  ess_platform_mutex_unlock(&task->runningMutex);

}
#endif
