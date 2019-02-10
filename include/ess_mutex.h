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
 * @file ess_mutex.h
 * @author Anna Sopdia Schröck
 * @date 10 Februar 20119
 * @brief all platform specific mutex functions
 *
 */
#ifndef _ESS_PLATFORM_MUTEX_H_
#define _ESS_PLATFORM_MUTEX_H_

#include "ess_error.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ess_platform_mutex {
  char name[16];
  void* handle;
}ess_platform_mutex_t;


/**
 * @brief create the mutex
 * @param [in] mtx the semaphore context
 * @param [in] name of the semaphore
 *
 * @retval ESS_OK no error
 * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_ERROR unspec error
 * @retval ESS_ERROR_NULL 'ess_platform_mutex_t' mtx is null
 */
ess_error_t ess_platform_mutex_create(ess_platform_mutex_t* mtx, const char* name);
/**
 * @brief destroy the mutex
 * @param [in] mtx pointer of the mutex srtruct
 *
 * @retval ESS_OK no error
 * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_ERROR unspec error
 * @retval ESS_ERROR_NOT_CREATED  mutex is not created
 * @retval ESS_ERROR_NULL 'ess_platform_mutex_t' mtx is null
 */
ess_error_t ess_platform_mutex_destroy(ess_platform_mutex_t* mtx);

/**
 * @brief lock the mutex
 * @param [in] mtx pointer of the mutex srtruct
 *
 * @retval ESS_OK no error
 * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_ERROR unspec error
 * @retval ESS_ERROR_NOT_CREATED  mutex is not created
 * @retval ESS_ERROR_NULL 'ess_platform_mutex_t' mtx is null
 */
ess_error_t ess_platform_mutex_lock(ess_platform_mutex_t* mtx);
/**
 * @brief unlock the mutex
 * @param [in] mtx pointer of the mutex srtruct
 *
 * @retval ESS_OK no error
 * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_ERROR unspec error
 * @retval ESS_ERROR_NOT_CREATED  mutex is not created
 * @retval ESS_ERROR_NULL 'ess_platform_mutex_t' mtx is null
 */
ess_error_t ess_platform_mutex_unlock(ess_platform_mutex_t* mtx);
/**
 * @brief try lock the mutex
 * @param [in] mtx pointer of the mutex srtruct
 *
 * @retval ESS_OK lock the mutex
 * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_ERROR can't lock
 * @retval ESS_ERROR_NULL 'ess_platform_mutex_t' mtx is null
 */
ess_error_t ess_platform_mutex_try_lock(ess_platform_mutex_t* mtx);
#ifdef __cplusplus
}
#endif

#endif
