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
 * @file ess_ipadress.h
 * @author Anna Sopdia Schröck
 * @date 28 April 2019
 * @brief basic ip adress handler
 */
 #ifndef _ESS_IPADRESS_H_
 #define _ESS_IPADRESS_H_

 #include "ess.h"
#include "ess_network.h"

class ess_ipaddress : public ess_object {
public:
  ess_ipaddress(ess_socket_fam fam) : ess_object("ess_ipaddress"), m_eFamily(fam) { }
  ess_ipaddress(ess_socket_fam fam, std::string name) : ess_object(name), m_eFamily(fam) { }

  ess_ipaddress(const ess_ipaddress& value) : ess_object(value) {
    m_eFamily = value.m_eFamily; m_bInvalid = value.m_bInvalid; }

  bool is_valid() { return !m_bInvalid; }
  ess_socket_fam get_family() { return m_eFamily; }

protected:
  ess_socket_fam m_eFamily;
  bool m_bInvalid;
};
using ess_ipaddress_t = ess_ipaddress;

/*






using ess_ip6address_t = ess_ip6address;
*/
#endif
