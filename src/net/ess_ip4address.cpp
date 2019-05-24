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


ess_ip4address::ess_ip4address(uint8_t first_octet, uint8_t second_octet,
  uint8_t third_octet, uint8_t fourth_octet, std::string name)
  :  ess_ipaddress(ESS_SOCKET_FAMILY_IP4, name) {

    address.bytes[0] = first_octet;
    address.bytes[1] = second_octet;
    address.bytes[2] = third_octet;
    address.bytes[3] = fourth_octet;

}
ess_ip4address::ess_ip4address(uint32_t addr, std::string name)
:  ess_ipaddress(ESS_SOCKET_FAMILY_IP4, name) {
    address.dword = addr;
}

ess_ip4address::ess_ip4address(const uint8_t *addr, std::string name)
:  ess_ipaddress(ESS_SOCKET_FAMILY_IP4, name) {

  address.bytes[0] = addr[0];
  address.bytes[1] = addr[1];
  address.bytes[2] = addr[2];
  address.bytes[3] = addr[3];

}

std::string ess_ip4address::to_string()  {
  std::ostringstream ss;
  ss << address.bytes[0]  << "." << address.bytes[1]  << ".";
  ss << address.bytes[2]  << "." <<address.bytes[3]  ;

  return ss.str();
}

bool ess_ip4address::from_string(const std::string str) {
    uint16_t acc = 0;
    uint8_t dots = 0;
    uint8_t bytes[4];

    const char* addr = str.c_str();

    while (*addr) {
        char c = *addr++;
        if (c >= '0' && c <= '9') {
            acc = acc * 10 + (c - '0');
            if (acc > 255) { return false; }
        } else if (c == '.')   {
            if (dots == 3) { return false;   }
            bytes[dots++] = acc;
            acc = 0;
        } else {
            return false;
        }
    }
    if (dots != 3) { return false; }
    bytes[3] = acc;

    // only cpy when pars ok is
    address.bytes[0] = bytes[0];
    address.bytes[1] = bytes[1];
    address.bytes[2] = bytes[2];
    address.bytes[3] = bytes[3];

    return true;
}

ess_ip4address& ess_ip4address::operator = (const uint8_t *addr) {
  address.bytes[0] = addr[0];
  address.bytes[1] = addr[1];
  address.bytes[2] = addr[2];
  address.bytes[3] = addr[3];
  return *this;
}
ess_ip4address& ess_ip4address::operator = (uint32_t addr) {
  address.dword = addr;
  return *this;
}
