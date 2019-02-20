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
 * @file ess_platform.h
 * @author Anna Sopdia Schröck
 * @date 3 Februar 2019
 * @brief  platform specific task class
 *
 */
#ifndef _H_
#define _H_

#include "ess_error.h"
#include "ess_mutex.h"

class ess_task {
public:
  ess_task() { }
  ess_task(const char* taskName, void* param, unsigned int stackSize);
  virtual ~ess_task() { }

  /**
   * @brief start the task
   * @retval ESS_OK
   * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
   * @retval ESS_ERROR
   * @retval ESS_ERROR_NULL 'esp_platform_task_t' task is null
   */
  ess_error_t start();
  /**
   * @brief delete the task
   * @retval ESS_OK
   * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
   * @retval ESS_ERROR
   * @retval ESS_ERROR_NULL 'esp_platform_task_t' task is null
   */
  ess_error_t destroy();


  /**
   * @brief suspend the task
   * @param[int] task The  pointer to the 'esp_platform_task_t' struct
   *
   * @retval ESS_OK
   * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
   * @retval ESS_ERROR
   * @retval ESS_ERROR_NULL 'esp_platform_task_t' task is null
   */
  ess_error_t suspend();
  /**
   * @brief resume the task
   * @param[int] task The  pointer to the 'esp_platform_task_t' struct
   *
   * @retval ESS_OK
   * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
   * @retval ESS_ERROR
   * @retval ESS_ERROR_NULL 'esp_platform_task_t' task is null
   */
  ess_error_t resume();

  virtual void onTask(ess_task* self, void* userdata) { }

private:
  static void int_task_stub(void* data);
protected:
  char m_strName[16];
  int m_iTaskId;

  void* m_pUserdata;
  void* parem;
  unsigned int m_uiStackSize;
  void* m_pHandle;
  int m_iPriority;
  bool m_bRunning;

  ess_mutex runningMutex;
  ess_mutex contextMutext;
  ess_mutex continuemutex;
  ess_mutex continuemutex2;
};


#endif
