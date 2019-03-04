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
 * @file ess_ontroler.h
 * @author Anna Sopdia Schröck
 * @date 04 März 20119
 * @brief generic platform hardware controller
 *
 *
 */
#ifndef _ESS_PLATFORM_CONTROLER_H_
#define _ESS_PLATFORM_CONTROLER_H_

#include "ess.h"

class ess_controler {
public:
  ess_controler() { m_bCreated = false; }
  virtual ~ess_controler() { destroy(); }
  
  virtual ess_error_t setup(int flags) { return ESS_OK; }
  virtual ess_error_t destroy(int flags) { return ESS_OK; }
protected:
  bool m_bCreated;
};


#endif
