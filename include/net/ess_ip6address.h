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

#define ESS_IP6ADRESS_ANY ess_ip6address_t( unsigned char[] { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, 0)
#define ESS_IP6ADRESS_LOOPBACK ess_ip6address_t( unsigned char[] { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },  0)
#define ESS_IP46DRESS_BROADCAST ess_ip6address_t( unsigned char[] { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, 0)

class ess_ip6address : public ess_ipaddress {
public:
  ess_ip6address();

  ess_ip6address(ess_ip4address v);
  ess_ip6address(const ess_ip6address& value);

  ess_ip6address(unsigned short address[16], long scopid)
    : ess_ip6address(address, scopid, "ess_ip6address") { }

  ess_ip6address(unsigned short address[16], long scopid, std::string name);

  void get_address(unsigned short b[16]);
  unsigned short* get_address() { return m_numbers; }

  long get_scopid() { return m_scopid; }
  void set_scopid(long id) { m_scopid = id; }

  ess_ip4address to_ip4();

  virtual std::string to_string();
protected:
  long m_scopid;
  unsigned short  m_numbers[8];
};

#endif
