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
#include "net/ess_ip6_end_point.h"
 #include <sstream>

 ess_ip6_end_point::ess_ip6_end_point()
   : ess_ip_end_point(ESS_SOCKET_FAMILY_IP6, 0, "ess_ip4_end_point")/*,
     m_ipAdress(ESS_IP6ADRESS_ANY)*/ {

 }
 ess_ip6_end_point::ess_ip6_end_point(ess_ip6address address, uint16_t port)
    : ess_ip_end_point(ESS_SOCKET_FAMILY_IP6, port, "ess_ip4_end_point"),
      m_ipAdress(address) { }

  ess_ip6_end_point::ess_ip6_end_point( ess_ip6address address,  uint16_t port, std::string name)
    : ess_ip_end_point(ESS_SOCKET_FAMILY_IP6, port, name),
      m_ipAdress(address) { }


std::string ess_ip6_end_point::to_string() {
  std::ostringstream ss;
  ss << "[" << m_ipAdress.to_string() << "]:" << m_iPort;
  return  ss.str();
}
