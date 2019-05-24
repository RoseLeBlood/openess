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
#include "net/ess_ip6address.h"
#include <sstream>


ess_ip6address::ess_ip6address(std::string name)
  : ess_ipaddress(ESS_SOCKET_FAMILY_IP6, name) {

    ess_zeromem(address.bytes, sizeof(address.bytes));
}
ess_ip6address::ess_ip6address(const uint32_t *addr, std::string name)
  : ess_ipaddress(ESS_SOCKET_FAMILY_IP6, name) {

    ess_memcpy(address.bytes, (const uint8_t *)addr, sizeof(address.bytes));
}
ess_ip6address::ess_ip6address(const uint8_t *addr, std::string name)
  : ess_ipaddress(ESS_SOCKET_FAMILY_IP6, name) {

    address.bytes[0] = addr[0];
    address.bytes[1] = addr[1];
    address.bytes[2] = addr[2];
    address.bytes[3] = addr[3];
    address.bytes[4] = addr[4];
    address.bytes[5] = addr[5];
    address.bytes[6] = addr[6];
    address.bytes[7] = addr[7];
    address.bytes[8] = addr[8];
    address.bytes[9] = addr[9];
    address.bytes[10] = addr[10];
    address.bytes[11] = addr[11];
    address.bytes[12] = addr[12];
    address.bytes[13] = addr[13];
    address.bytes[14] = addr[14];
    address.bytes[15] = addr[15];

}

ess_ip6address& ess_ip6address::operator = (const uint8_t *addr) {
  address.bytes[0] = addr[0];
  address.bytes[1] = addr[1];
  address.bytes[2] = addr[2];
  address.bytes[3] = addr[3];
  address.bytes[4] = addr[4];
  address.bytes[5] = addr[5];
  address.bytes[6] = addr[6];
  address.bytes[7] = addr[7];
  address.bytes[8] = addr[8];
  address.bytes[9] = addr[9];
  address.bytes[10] = addr[10];
  address.bytes[11] = addr[11];
  address.bytes[12] = addr[12];
  address.bytes[13] = addr[13];
  address.bytes[14] = addr[14];
  address.bytes[15] = addr[15];
  return *this;
}


std::string ess_ip6address::to_string()
{
    char szRet[40];
    sprintf(szRet,"%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
            address.bytes[0], address.bytes[1], address.bytes[2], address.bytes[3],
            address.bytes[4], address.bytes[5], address.bytes[6], address.bytes[7],
            address.bytes[8], address.bytes[9], address.bytes[10], address.bytes[11],
            address.bytes[12], address.bytes[13], address.bytes[14], address.bytes[15]);
    return std::string(szRet);
}
