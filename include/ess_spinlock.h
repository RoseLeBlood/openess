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
 * @file ess_spinlock.h
 * @author Anna Sopdia Schröck
 * @date 11 Februar 20119
 * @brief all platform specific spinlock functions
 *
 */
#ifndef _ESS_PLATFORM_SPINLOCK_H_
#define _ESS_PLATFORM_SPINLOCK_H_

#include "ess_error.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ess_platform_spinlock {
  char name[16];
  void* handle;
  int count;
}ess_platform_spinlock_t;


/**
 * @brief create the spinlock
 * @param [in] spi the spinlock struct
 * @param [in] name of the spinlock
 *
 * @retval ESS_OK no error
 * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_ERROR unspec error
 * @retval ESS_ERROR_NULL 'ess_platform_spinlock_t' spi is null
 */
ess_error_t ess_platform_spinlock_create(ess_platform_spinlock_t* spi, const char* name, int count);
/**
 * @brief destroy the spinlock
 * @param [in] spi pointer of the spinlock srtruct
 *
 * @retval ESS_OK no error
 * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_ERROR unspec error
 * @retval ESS_ERROR_NOT_CREATED  spinlock is not created
 * @retval ESS_ERROR_NULL 'ess_platform_spinlock_t' spi is null
 */
ess_error_t ess_platform_spinlock_destroy(ess_platform_spinlock_t* spi);

/**
 * @brief lock the spinlock
 * @param [in] spi pointer of the spinlock srtruct
 *
 * @retval ESS_OK no error
 * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_ERROR unspec error
 * @retval ESS_ERROR_NOT_CREATED  spinlock is not created
 * @retval ESS_ERROR_NULL 'ess_platform_spinlock_t' spi is null
 */
ess_error_t ess_platform_spinlock_lock(ess_platform_spinlock_t* spi);

/**
 * @brief try lock the spinlock
 * @param [in] spi pointer of the spinlock srtruct
 *
 * @retval ESS_OK lock the spinlock
 * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_ERROR can't lock
 * @retval ESS_ERROR_NULL 'ess_platform_spinlock_t' spi is null
 */
ess_error_t ess_platform_spinlock_try_lock(ess_platform_spinlock_t* spi);
/**
 * @brief unlock the spinlock
 * @param [in] spi pointer of the spinlock srtruct
 *
 * @retval ESS_OK no error
 * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_ERROR unspec error
 * @retval ESS_ERROR_NOT_CREATED  spinlock is not created
 * @retval ESS_ERROR_NULL 'ess_platform_spinlock_t' spi is null
 */
ess_error_t ess_platform_spinlock_unlock(ess_platform_spinlock_t* spi);

#ifdef __cplusplus
}
#endif

#endif
