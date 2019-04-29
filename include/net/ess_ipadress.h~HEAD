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
<<<<<<< HEAD:include/net/ess_inet_stream_server.h
 * @date 29 April 2019
=======
 * @date 28 April 2019
 * @brief basic ip adress handler
>>>>>>> 92de4c3f13a31f0e4b5904d64c8040017622b2c8:include/net/ess_ipadress.h
 */
 #ifndef _ESS_IPADRESS_H_
 #define _ESS_IPADRESS_H_

<<<<<<< HEAD:include/net/ess_inet_stream_server.h
#ifndef _ESS_INET_STREAM_SERVER_H_
#define _ESS_INET_STREAM_SERVER_H_

class ess_inet_stream_server {
public:
  virtual ess_error_t listen(int optons) = 0;

  virtual uint32_t write(const void* data, size_t offset, size_t size) = 0;
  virtual uint32_t read(void* data, size_t offset, size_t size) = 0;
=======
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
>>>>>>> 92de4c3f13a31f0e4b5904d64c8040017622b2c8:include/net/ess_ipadress.h
};
using ess_ipaddress_t = ess_ipaddress;

<<<<<<< HEAD:include/net/ess_inet_stream_server.h
=======
/*






using ess_ip6address_t = ess_ip6address;
*/
>>>>>>> 92de4c3f13a31f0e4b5904d64c8040017622b2c8:include/net/ess_ipadress.h
#endif
