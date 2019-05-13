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
 * @file ess_lockable_object.h
 * @author Anna Sopdia Schröck
 * @date 15 Mai 2019
 */
#ifndef _ESS_LOCKABLE_OBJECT_H_
#define _ESS_LOCKABLE_OBJECT_H_

#include "task/ess_autolock.h"

class ess_lockable_object : public ess_lock {
public:
  ess_lockable_object()
    : ess_lock("ess_object") {  create(); }

  ess_lockable_object(std::string name)
    : ess_lock(name) {  create(); }

  ess_lockable_object(const ess_lockable_object& other)  = delete;
  ess_lockable_object(const ess_lockable_object&& other)  = delete;

  virtual ess_error_t create() { return m_pMutex.create(); }
  virtual ess_error_t destroy()  { return m_pMutex.destroy(); }

  virtual ess_error_t lock() { return m_pMutex.lock(); }
  virtual ess_error_t unlock()  { return m_pMutex.unlock(); }
  virtual ess_error_t try_lock() { return m_pMutex.try_lock(); }

  virtual std::string get_name() {
    ess_automux_t lock(m_pMutex); return m_strName; }

  virtual void set_name(const std::string name) {
    ess_automux_t lock(m_pMutex); ess_lock::set_name(name); }

  virtual std::string to_string() {
     ess_automux_t lock(m_pMutex); return ess_lock::to_string();  }

  virtual void from_string(const std::string str) {
    ess_automux_t lock(m_pMutex); ess_lock::set_name(str); }

protected:
  ess_mutex m_pMutex;
};

 using ess_autolock_t = ess_autolock<ess_lockable_object>;

#endif
