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
 * @file ess_task_group.h
 * @author Anna Sopdia Schröck
 * @date 19 Mai 2019
 */
#ifndef _ESS_TASK_GROUP_H_
#define _ESS_TASK_GROUP_H_

#include "ess_task.h"
#include "ess_lockable_object.h"

#include <list>

class ess_task_group : public ess_lockable_object {
public:
  ess_task_group() : ess_lockable_object() { m_bIsStarted = false; }
  ess_task_group(const std::string groupname)
    : ess_lockable_object(groupname) { m_bIsStarted = false;  }

    virtual ess_error_t start() ;
    virtual ess_error_t start(uint32_t core) ;
    virtual ess_error_t destroy();
    virtual ess_error_t suspend();
    virtual ess_error_t resume();

    ess_error_t add(ess_task* node) ;

    virtual void clear();

    virtual ess_task_group& operator +=  (ess_task* node) {
      add(node); return *this; }

    void set_user_data(void* data);
protected:
  std::list<ess_task*> m_listTasks;
  bool m_bIsStarted;
};

#endif
