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
 * @file ess_ip6address.h
 * @author Anna Sopdia Schröck
 * @date 28 April 2019
 * @brief class for IP Adress version 6
 */

 #ifndef _ESS_IP6ADRESS_H_
 #define _ESS_IP6ADRESS_H_

#include "ess_ipadress.h"
#include "ess_ip4address.h"


#define ESS_IP6ADRESS_ANY ess_ip6address( "ESS_IP4ADRESS_ANY")

class ess_ip6address : public ess_ipaddress {
public:
  union {
        uint8_t bytes[16];
        uint32_t dword[4];
    } address;

    ess_ip6address()
      :  ess_ip6address("ESS_IP4ADRESS_ANY") { }

    ess_ip6address(const uint8_t *address)
      :  ess_ip6address(address, "ess_ip6address") { }
    ess_ip6address(const uint32_t *address)
       :  ess_ip6address(address, "ess_ip6address") { }

    ess_ip6address(std::string name);
    ess_ip6address(const uint8_t *address, std::string name);
    ess_ip6address(const uint32_t *address, std::string name);

    virtual ~ess_ip6address() {}

    virtual std::string to_string();


    operator const uint8_t*() const { return address.bytes; }
    operator const uint32_t*() const {  return address.dword;  }

    uint8_t operator [] (int index) const   {   return address.bytes[index]; }
    uint8_t& operator[](int index) { return address.bytes[index]; }

    ess_ip6address& operator = (const uint8_t *address);

    bool is_equels(const ess_ip6address& other)  const {
        return (address.dword[0] == other.address.dword[0])
            && (address.dword[1] == other.address.dword[1])
            && (address.dword[2] == other.address.dword[2])
            && (address.dword[3] == other.address.dword[3]);
    }
};

inline bool operator == (const ess_ip6address& a, const ess_ip6address& b) {
  return a.is_equels(b);
}
inline bool operator != (const ess_ip6address& a, const ess_ip6address& b) {
  return !(a.is_equels(b) );
}

#endif
