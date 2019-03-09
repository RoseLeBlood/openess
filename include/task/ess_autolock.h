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
 * @date 09 März 2019
 * @brief autolock helper class
 *
 */

 #ifndef _ESS_AUTOLOCK_H_
 #define _ESS_AUTOLOCK_H_

#include "ess_error.h"
#include "task/ess_task.h"
#include "task/ess_spinlock.h"

 /**
 * @addtogroup task
 * @{
 */

 template <class LOCK>
 class  ess_autolock
 {
 public:
 	ess_autolock(LOCK &m) : m_ref_lock(m) {
     m_ref_lock.lock();
   }
 	~ess_autolock() {
      m_ref_lock.unlock();
    }
 private:
 	LOCK &m_ref_lock;
 };

 using ess_autospin_t = ess_autolock<ess_spinlock>;
 using ess_automux_t = ess_autolock<ess_mutex>;


 /**
 * @}
 */
 #endif
