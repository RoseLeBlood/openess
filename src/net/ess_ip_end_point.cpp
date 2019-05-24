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

#include "net/ess_ip_end_point.h"

ess_ip_end_point::ess_ip_end_point()
 : ess_end_point(ESS_SOCKET_FAMILY_ALG) {
   set_port(0);
 }



ess_ip_end_point::ess_ip_end_point(ess_ip6address address, uint32_t port)
  : ess_end_point(ESS_SOCKET_FAMILY_IP6, "ess_ip_end_point") {
    m_ip6 = address;
    m_bInValid =  (port == 0 && port<=0x0000FFFF);
}
ess_ip_end_point::ess_ip_end_point(ess_ip4address address, uint32_t port)
  : ess_end_point(ESS_SOCKET_FAMILY_IP4, "ess_ip_end_point") {
    m_ip4 = address;
    m_bInValid =  (port == 0 && port<=0x0000FFFF);
}
ess_ip_end_point::ess_ip_end_point(ess_ip6address address, uint32_t port, std::string name)
  : ess_end_point(ESS_SOCKET_FAMILY_IP6, "ess_ip_end_point") {
    m_ip6 = address;
    m_bInValid =  (port == 0 && port<=0x0000FFFF);
}
ess_ip_end_point::ess_ip_end_point(ess_ip4address address, uint32_t port, std::string name)
  : ess_end_point(ESS_SOCKET_FAMILY_IP4, name) {
    m_ip4 = address;
    m_bInValid =  (port == 0 && port<=0x0000FFFF);
}

std::string ess_ip_end_point::to_string() {
  std::ostringstream ss;
  ss << "[" <<  m_ip4.to_string()  << " (" << m_ip6.to_string() << ")] : " << m_iPort;
  return  ss.str();
}

void ess_ip_end_point::set_port(uint32_t port) {
    m_iPort = port;
    m_bInValid =  (port == 0 && port<=0x0000FFFF);
}
