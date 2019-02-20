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
 * @brief all basic platform specific functions
 *
 */
#ifndef _ESS_PLATFORM_H_
#define _ESS_PLATFORM_H_

#include "ess_error.h"



#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief get the time in milliseconds since the  scheduler started.
 * @retval >0  the time in milliseconds since the scheduler started.
 *@reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_ERROR
 */
unsigned int ess_platform_get_tick_count();
/**
 * @brief Sleep for the specified number of seconds.
 * @param [in] secs the period in seconds for which to sleep.
 * @retval ESS_OK
 *@reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
 */
ess_error_t ess_platform_sleep(unsigned int secs);
/**
 * @brief Sleep for the specified number of useconds.
 * @param [in] secs the period in useconds for which to sleep.
 * @retval ESS_OK
 *@reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
 */
int ess_platform_usleep(unsigned int usec);
/**
 * @brief Sleep for the specified number of nanoseconds.
 * @param [in] req
 * @param [in] rem
 * @retval ESS_OK
 *@reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
 */
int ess_platform_nsleep(const struct timespec *req, struct timespec *rem);

/**
 * @brief get microseconds since start
 * @reval -1  function is for using platform not implantiert
 * @return the microseconds since start
 */
unsigned long ess_platform_micros();
/**
 * @brief get milliseconds since start
 * @reval -1  function is for using platform not implantiert
 * @return the milliseconds since start
 */
unsigned long ess_platform_millis();

#ifdef __cplusplus
}
#endif

#endif
