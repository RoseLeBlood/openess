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
 * @file ess_lock..h
 * @author Anna Sopdia Schröck
 * @date 13 Februar 2019
 * @brief lock interface
 *
 */
#ifndef _ESS_PLATFORM_ILOCK_H_
#define _ESS_PLATFORM_ILOCK_H_

#include "ess.h"

/**
* @addtogroup task
* @{
*/

class ess_lock : public ess_object {
public:
  ess_lock() : ess_object("ess_lock") { }
  ess_lock(const std::string name) : ess_object(name) { }

  virtual ess_error_t create() = 0;
  virtual ess_error_t destroy() = 0;

  virtual ess_error_t lock() = 0;
  virtual ess_error_t unlock() = 0;
  virtual ess_error_t try_lock() = 0;

  virtual bool operator == (const ess_lock& other) {
    return (m_pHandle == other.m_pHandle );
  }
  virtual bool operator != (const ess_lock& other) {
    return (m_pHandle != other.m_pHandle);
  }
protected:
  void* m_pHandle;
};
/**
* @}
*/
#endif
