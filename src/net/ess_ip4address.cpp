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
#include "net/ess_ip4address.h"
#include <sstream>

ess_ip4address::ess_ip4address(unsigned short address[4], std::string name)
  : ess_ipaddress(ESS_SOCKET_FAMILY_IP4, name) {
    m_bInvalid = false;

    m_iAddress = ((address[3] << 24 | address[2] <<16 |
                              address[1] << 8| address[0]) & 0x0FFFFFFFF);

}


void ess_ip4address::get_address(unsigned short b[4]) {
  b[0] = (unsigned short)(m_iAddress);
  b[1] = (unsigned short)(m_iAddress >> 8);
  b[2] = (unsigned short)(m_iAddress >> 16);
  b[3] = (unsigned short)(m_iAddress >> 24);
}


std::string ess_ip4address::to_string() {
  std::ostringstream ss;
  ss << ((m_iAddress >> 24) & 0xFF) << "." << ((m_iAddress >> 16) & 0xFF)  << ".";
  ss << ((m_iAddress >>  8) & 0xFF) << "." << ((m_iAddress          ) & 0xFF) ;

  return ss.str();
}
