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
 * @file ess_singleton_object.h
 * @author Anna Sopdia Schröck
 * @date 15 Mai 2019
 */
#ifndef _ESS_SINGLETON_OBJECT_H_
#define _ESS_SINGLETON_OBJECT_H_

#include "ess_lockable_object.h"
#include "task/ess_auto_mutex.h"

#define ESS_SINGLETON(X) friend class ess_singleton_object<X>;

template<class TOBJECT>
class ess_singleton_object : public ess_lockable_object {
protected:
  ess_singleton_object()
    : ess_lockable_object("ess_singleton_object") { }

public:
  ess_singleton_object(const ess_singleton_object&) = delete;
  ess_singleton_object(const ess_singleton_object&&) = delete;

  static TOBJECT& instance() {
    static ess_auto_mutex _creatingMutex("ess_singleton_creating_mutex");

    if(m_pSingleton == nullptr) {
      _creatingMutex.lock();

      if(m_pSingleton == nullptr)
        m_pSingleton = new TOBJECT();

      _creatingMutex.unlock();
    }

    return *m_pSingleton;
  }
private:
  static TOBJECT* m_pSingleton;
};
template<class TOBJECT>
TOBJECT* ess_singleton_object<TOBJECT>::m_pSingleton = nullptr;


#endif
