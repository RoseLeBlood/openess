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
 * @file ess_ip_end_point.h
 * @author Anna Sopdia Schröck
 * @date 28 April 2019
 */

 #ifndef _ESS_IP_ENDPOINT_H_
 #define _ESS_IP_ENDPOINT_H_

 #include "ess_end_point.h"
#include "ess_ip6address.h"

 #define ESS_IP4ENDPOINT_ANY ess_ip_end_point (ESS_IP4ADRESS_ANY, 0)

 class ess_ip_end_point : public ess_end_point {
 public:
   ess_ip_end_point();
   ess_ip_end_point(ess_ip6address address, uint32_t port);
   ess_ip_end_point(ess_ip4address address, uint32_t port);

   ess_ip_end_point(ess_ip6address address, uint32_t port, std::string name);
   ess_ip_end_point(ess_ip4address address, uint32_t port, std::string name);

  virtual uint16_t get_port() const { return m_iPort; }
  virtual void set_port(uint32_t port);

  virtual bool is_valid() const { return !m_bInValid; }

  virtual ess_ip4address get_address_ip4()  { return m_ip4; }
  virtual ess_ip6address get_address_ip6()  { return m_ip6; }

  virtual std::string to_string();
 protected:
   uint32_t m_iPort;
   bool m_bInValid;
   ess_ip6address m_ip6;
   ess_ip4address m_ip4;
 };

 #endif
