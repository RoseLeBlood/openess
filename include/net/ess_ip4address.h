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


#define ESS_IP4ADRESS_ANY ess_ip4address(0, 0, 0, 0,  "ESS_IP4ADRESS_ANY")

class ess_ip4address : ess_ipaddress {
public:
  union {
        uint8_t bytes[4];
        uint32_t dword;
    } address;

  // Constructors
  ess_ip4address()
    : ess_ip4address(0, 0, 0, 0,  "ANY") { }

  ess_ip4address(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet)
    :   ess_ip4address(first_octet, second_octet, third_octet, fourth_octet, "ess_ip4address") { }

  ess_ip4address(uint32_t address)
    : ess_ip4address(address,  "ess_ip4address") { }

  ess_ip4address(const uint8_t *address)
    : ess_ip4address(address,  "ess_ip4address") { }

  ess_ip4address(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet,
      uint8_t fourth_octet, std::string name);

  ess_ip4address(uint32_t address, std::string name);

  ess_ip4address(const uint8_t *address, std::string name);

  virtual ~ess_ip4address() { }

  virtual std::string to_string() ;
  virtual bool from_string(const std::string str);

  ess_ip4address& operator =(const uint8_t *address);
  ess_ip4address& operator = (uint32_t address);

  operator uint32_t() const {
    return address.dword; }

  uint8_t operator []  (int index) const {
    return address.bytes[index]; }

  uint8_t& operator [] (int index) {
      return address.bytes[index];   }

  bool is_equels(const ess_ip4address& other) const {
     return address.dword == other.address.dword;   }
};

using ess_ip4address_t = ess_ip4address;




#endif
