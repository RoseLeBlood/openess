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
 * @date 11 Februar 2019
 * @brief  platform specific spinlock class
 *
 */
#ifndef _ESS_PLATFORM_SPINLOCK_H_
#define _ESS_PLATFORM_SPINLOCK_H_

#include "ess_lock.h"

class ess_spinlock : public ess_lock {
public:
  ess_spinlock();
  ~ess_spinlock();

  virtual ess_error_t create(int count);
  virtual ess_error_t destroy();

  /**
   * @brief lock the spinlock
   * @retval ESS_OK no error
   * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
   * @retval ESS_ERROR unspec error
   * @retval ESS_ERROR_NOT_CREATED  mutex is not created
   * @retval ESS_ERROR_NULL 'ess_platform_mutex_t' mtx is null
   */
  virtual ess_error_t lock();
  /**
   * @brief unlock the spinlock
   * @retval ESS_OK no error
   * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
   * @retval ESS_ERROR unspec error
   * @retval ESS_ERROR_NOT_CREATED  mutex is not created
   * @retval ESS_ERROR_NULL 'ess_platform_mutex_t' mtx is null
   */
  virtual ess_error_t unlock();

  /**
   * @brief try lock the mutex
   *
   * @retval ESS_OK lock the mutex
   * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
   * @retval ESS_ERROR can't lock
   * @retval ESS_ERROR_NULL 'ess_platform_mutex_t' mtx is null
   */
  virtual ess_error_t try_lock();

};

#endif
