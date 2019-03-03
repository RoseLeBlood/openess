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
 * @file ess_backend_factory.cpp
 * @author Anna Sopdia Schröck
 * @date 18 Februar 2019
 * @brief Contains  backend root class source
 *
 *
 */

#include "ess_backend_factory.h"


bool ess_backend_platform::add_backend(ess_backend* backend) {
  if(backend == 0) return false;
  m_lBackends.insert(std::pair<std::string, ess_backend*>(backend->get_name(), backend)) ;
  return true;
}

ess_backend* ess_backend_platform::get_backend(const std::string name) {
  if(m_lBackends[name] == NULL) return 0;
  if(m_lBackends[name]->is_used()) return 0;

  return m_lBackends[name];
}
