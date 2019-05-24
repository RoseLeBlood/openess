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
 * @file ess_auto_mutex.h
 * @author Anna Sopdia Schröck
 * @date 16 Mai 2019
 */
 #ifndef _ESS_PLATFORM_AUTO_MUTEX_H_
 #define _ESS_PLATFORM_AUTO_MUTEX_H_

#include "task/ess_mutex.h"

class ess_auto_mutex : public ess_mutex {
public:
  ess_auto_mutex() : ess_mutex() { create();  }
  ess_auto_mutex(const std::string name) : ess_mutex(name) { create(); }

  ~ess_auto_mutex() { destroy(); }
};



#endif
