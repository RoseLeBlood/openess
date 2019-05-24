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
 * @file esp32_platform_task.cpp
 * @author Anna Sopdia Schröck
 * @date 3 Februar 2019
 * @brief all esp32 platform task functions source
 *
 */
#include "config.h"
#ifdef ESS_CONFIC_TASK_ESP32

#include "ess_platform.h"
#include "task/ess_task.h"

#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#define LOG_TAG  "OesSpT"

static int task_id = 0;


ess_task::ess_task(const std::string taskName, void* param, unsigned int stackSize)
  : ess_object(taskName) {

  m_uiStackSize = stackSize;
  m_pUserdata = param;
  m_iTaskId = task_id++;

  m_pHandle = 0;
  m_iPriority = 5;
  m_bRunning = false;


}
ess_error_t ess_task::start() {
  if(continuemutex.create() != ESS_OK) return ESS_ERROR_TASK_CREAT;
  if(continuemutex2.create()!= ESS_OK) return ESS_ERROR_TASK_CREAT;
  if(runningMutex.create()!= ESS_OK) return ESS_ERROR_TASK_CREAT;
  if(contextMutext.create()!= ESS_OK) return ESS_ERROR_TASK_CREAT;

  continuemutex.lock();
  runningMutex.lock();

  if (m_bRunning) {
    continuemutex.unlock();
    runningMutex.unlock();
    return ESS_ERROR_TASK_RUNNING;
  }
  runningMutex.unlock();

  xTaskCreate( int_task_stub, get_name().c_str(), m_uiStackSize, this , m_iPriority,  &m_pHandle);

  continuemutex.unlock();

  return ESS_OK;
}
ess_error_t ess_task::start(uint32_t core) {
  if(continuemutex.create() != ESS_OK) return ESS_ERROR_TASK_CREAT;
  if(continuemutex2.create()!= ESS_OK) return ESS_ERROR_TASK_CREAT;
  if(runningMutex.create()!= ESS_OK) return ESS_ERROR_TASK_CREAT;
  if(contextMutext.create()!= ESS_OK) return ESS_ERROR_TASK_CREAT;

  continuemutex.lock();
  runningMutex.lock();

  if (m_bRunning) {
    continuemutex.unlock();
    runningMutex.unlock();
    return ESS_ERROR_TASK_RUNNING;
  }
  runningMutex.unlock();

  xTaskCreatePinnedToCore( int_task_stub, get_name().c_str(), m_uiStackSize, this , m_iPriority,  &m_pHandle, core);

  continuemutex.unlock();

  return ESS_OK;
}
ess_error_t ess_task::destroy() {
  continuemutex.lock();
  runningMutex.lock();

  if (!m_bRunning) {
    if(m_pHandle == 0) return ESS_ERROR_NULL;

    continuemutex.unlock();
    runningMutex.unlock();
    return ESS_OK;
  }

  vTaskDelete(m_pHandle); m_pHandle = 0;
  m_bRunning = 0;

  continuemutex.unlock();
  runningMutex.unlock();

  continuemutex.destroy();
  continuemutex2.destroy();
  runningMutex.destroy();
  contextMutext.destroy();

  return ESS_OK;
}

ess_error_t ess_task::suspend() {
  if(m_pHandle == 0) return ESS_ERROR_NULL;

  runningMutex.lock();
  vTaskSuspend( m_pHandle );
  runningMutex.unlock();
  return ESS_OK;
}
ess_error_t ess_task::resume() {
  if(m_pHandle == 0) return ESS_ERROR_NULL;

  runningMutex.lock();
  vTaskResume( m_pHandle );
  runningMutex.unlock();

  return ESS_OK;
}
void ESS_IRAM_ATTR ess_task::int_task_stub(void* data) {
  ess_task* task; task = static_cast<ess_task*>(data);
  if(task != NULL) {
    task->continuemutex2.lock();
    task->runningMutex.lock();
    task->m_bRunning = true;
    task->runningMutex.unlock();

    task->continuemutex.lock();
    task->continuemutex.unlock();

    task->continuemutex2.unlock();

      task->onTask(task->m_pUserdata);

    task->runningMutex.lock();
    task->m_bRunning = false;
    vTaskDelete(task->m_pHandle);
    task->runningMutex.unlock();
  }
}

#endif
