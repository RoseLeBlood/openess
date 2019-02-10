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
 * @date 3 Februar 20119
 * @brief all platform specific task functions
 *
 */
#ifndef _ESS_PLATFORM_TASK_H_
#define _ESS_PLATFORM_TASK_H_

#include "ess_error.h"
#include "ess_mutex.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ess_platform_task {
  char name[16];
  int task_id;

  void* userdata;
  void* parem;
  unsigned int stack_size;
  void* handle;
  int priority;
  int running;

  ess_platform_mutex_t runningMutex;
  ess_platform_mutex_t contextMutext;
  ess_platform_mutex_t continuemutex;
  ess_platform_mutex_t continuemutex2;

  void (* task_stub)( void* userdata );
}ess_platform_task_t;


ess_error_t ess_platform_task_create(ess_platform_task_t* task, void task_func(void*),
    const char* taskName, void* param, unsigned int stackSize);
/**
 * @brief start the task
 * @param[int] task The  pointer to the 'esp_platform_task_t' struct
 *
 * @retval ESS_OK
 * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_ERROR
 * @retval ESS_ERROR_NULL 'esp_platform_task_t' task is null
 */
ess_error_t ess_platform_task_start(ess_platform_task_t* task);
/**
 * @brief delete the task
 * @param[int] task The  pointer to the 'esp_platform_task_t' struct
 *
 * @retval ESS_OK
 * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_ERROR
 * @retval ESS_ERROR_NULL 'esp_platform_task_t' task is null
 */
ess_error_t ess_platform_task_delete(ess_platform_task_t* task);

/**
 * @brief suspend the task
 * @param[int] task The  pointer to the 'esp_platform_task_t' struct
 *
 * @retval ESS_OK
 * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_ERROR
 * @retval ESS_ERROR_NULL 'esp_platform_task_t' task is null
 */
ess_error_t ess_platform_task_suspend(ess_platform_task_t* task);
/**
 * @brief resume the task
 * @param[int] task The  pointer to the 'esp_platform_task_t' struct
 *
 * @retval ESS_OK
 * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_ERROR
 * @retval ESS_ERROR_NULL 'esp_platform_task_t' task is null
 */
ess_error_t ess_platform_task_resume(ess_platform_task_t* task);


#ifdef __cplusplus
}
#endif

#endif
