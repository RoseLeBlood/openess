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
 * @file ess_platform_linux.h
 * @author Anna Sopdia Schröck
 * @date 18 Februar 20119
 * @brief Contains the linux platform factory pool
 *
 *
 */
#ifndef _ESS_PLATFORM_INC_LINUX_H_
#define _ESS_PLATFORM_INC_LINUX_H_


#include "ess_backend_factory.h"

#ifdef ESS_ENABLE_BACKEND_OPENAL
#include "platform/generic_openal_backend.h"
#endif

class ess_backend_linux : public ess_backend_platform {
public:
  ess_backend_linux() {
  }
  virtual void create() {
    #ifdef ESS_ENABLE_BACKEND_OPENAL
      add_backend(new generic_openal_backend());
    #endif
  }
  virtual std::string get_platform_name() {
    return std:string("Linux");
  }
  virtual std::string get_factory_creater() {
    return std:string("Anna_Sophia Schroeck - annasophia.schroeck@gmail.com");
  }
};



#endif
