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
 * @file ess_endpoint.h
 * @author Anna Sopdia Schröck
 * @date 28 April 2019
 */

 #ifndef _ESS_ENDPOINT_H_
 #define _ESS_ENDPOINT_H_

#include "ess_network.h"

class ess_end_point : public  ess_object {
public:
  ess_end_point()
    : ess_end_point(ESS_SOCKET_FAMILY_ALG) { }

  ess_end_point(ess_socket_fam_t fam)
    : ess_object("ess_end_point") { }

  ess_end_point(ess_socket_fam_t fam, std::string name)
    : ess_object(name), m_fFam(fam) { }

  ess_end_point(const ess_end_point& other)
    : ess_object(other), m_fFam(other.m_fFam) { }

  ess_end_point(const ess_end_point&& other)
    : ess_object(other), m_fFam(other.m_fFam) { }

  virtual ess_socket_fam_t get_family()  { return m_fFam; }
protected:
  ess_socket_fam_t m_fFam;
};

 #endif
