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
 * @file ess_ip4address.h
 * @author Anna Sopdia Schröck
 * @date 28 April 2019
 * @brief class for IP Adress version 4
 */

 #ifndef _ESS_IP4ADRESS_H_
 #define _ESS_IP4ADRESS_H_

#include "ess_ipadress.h"

#define ESS_IP4ADRESS_ANY ess_ip4address(0x0000000000000000, "ess_ipaddress::any")
#define ESS_IP4ADRESS_LOOPBACK ess_ip4address(0x000000000100007F, "ess_ipaddress::loopback")
#define ESS_IP4ADRESS_BROADCAST ess_ip4address(0x00000000FFFFFFFF, "ess_ipaddress::broadcast")
#define ESS_IP4ADRESS_NONE  ess_ip4address(0x00000000FFFFFFFF, "ess_ipaddress::none")


class ess_ip4address : public ess_ipaddress {
public:
  ess_ip4address();
  ess_ip4address( int address);
  ess_ip4address( int address, std::string name);

  ess_ip4address(unsigned short address[4]) : ess_ip4address(address, "ess_ip4address") { }
  ess_ip4address(unsigned short address[4], std::string name) ;

  unsigned int get_address() { return m_iAddress; }
  void             get_address(unsigned short b[4]);

  virtual std::string to_string();
protected:
  unsigned int m_iAddress;
};
/*
bool operator == (const ess_ip4address& a, const ess_ip4address& b)  {
  return a.get_address() == b.get_address();
}
bool operator != (const ess_ip4address& a, const ess_ip4address& b)  {
  return a.get_address() != b.get_address();
}

bool operator <= (const ess_ip4address& a, const ess_ip4address& b)  {
  return a.get_address() <= b.get_address();
}
bool operator >= (const ess_ip4address& a, const ess_ip4address& b)  {
  return a.get_address() >= b.get_address();
}

bool operator < (const ess_ip4address& a, const ess_ip4address& b)  {
  return a.get_address() < b.get_address();
}
bool operator > (const ess_ip4address& a, const ess_ip4address& b)  {
  return a.get_address() > b.get_address();
}
*/
using ess_ip4address_t = ess_ip4address;

#endif
