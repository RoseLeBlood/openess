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
 : ess_ip_end_point(ESS_SOCKET_FAMILY_ALG, 0) { }

ess_ip_end_point::ess_ip_end_point(ess_socket_fam_t fam)
 : ess_ip_end_point(fam, 0) { }

ess_ip_end_point::ess_ip_end_point(ess_socket_fam_t fam, uint16_t port)
 : ess_ip_end_point(fam, port, "ess_ip_end_point") { }

ess_ip_end_point::ess_ip_end_point(ess_socket_fam_t fam, uint16_t port, std::string name)
  : ess_end_point(fam, name), m_iPort(port) {
    m_bInValid = (port == 0);
}
void ess_ip_end_point::set_port(uint32_t port) {
    m_iPort = port;
    m_bInValid =  (port == 0 && port<=0x0000FFFF);
}
