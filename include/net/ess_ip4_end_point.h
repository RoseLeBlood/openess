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
 * @file ess_ip4_end_point.h
 * @author Anna Sopdia Schröck
 * @date 28 April 2019
 */

 #ifndef _ESS_IP_V4_ENDPOINT_H_
 #define _ESS_IP_V4_ENDPOINT_H_

 #include "ess_ip_end_point.h"
#include "ess_ip4address.h"

 #define ESS_IP4ENDPOINT_ANY ess_ip4_end_point(ESS_IP4ADRESS_ANY, 0)


 class ess_ip4_end_point : public ess_ip_end_point {
 public:
   ess_ip4_end_point();

   ess_ip4_end_point(ess_ip4address address, uint16_t port);
   ess_ip4_end_point( ess_ip4address address,  uint16_t port, std::string name);

   virtual ess_ip4address get_address()  { return m_ipAdress; }
   virtual std::string to_string() ;
 protected:
   ess_ip4address m_ipAdress;
 };


 #endif
