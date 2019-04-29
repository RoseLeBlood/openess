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
 * @file ess_endpoint.h
 * @author Anna Sopdia Schröck
 * @date 28 April 2019
 * @brief class forip endpoint
 */

 #ifndef _ESS_ENDPOINT_H_
 #define _ESS_ENDPOINT_H_

#include "ess_ip6address.h"
#include <sstream>



#define ESS_IP4ENDPOINT_ANY ess_ip_endpoint4_t(ESS_IP4ADRESS_ANY, 0)
#define ESS_IP6ENDPOINT_ANY ess_ip_endpoint4_t(ESS_IP6ADRESS_ANY, 0)

template <class IPTYPE >
class ess_ip_end_point : public ess_object {
public:
  ess_ip_end_point()
    : ess_object("ess_ip_end_point") { }

  ess_ip_end_point(IPTYPE address, int port)
    : ess_object("ess_ip_end_point"),
    m_ipAdress(address), m_iPort(port),
    m_bInvalid(port>= 0 && port<=0x0000FFFF) { }

  ess_socket_fam get_family() {
    return m_ipAdress.get_family();
  }

  IPTYPE get_address() { return m_ipAdress; }
  int get_port() { return m_iPort; }

  void set_address(IPTYPE addr) { m_ipAdress = addr; }
  void set_port(uint32_t port) { m_iPort = port; }

  bool is_valid() { return !m_bInvalid; }

  virtual std::string to_string() {
    std::ostringstream ss;
    ss << m_ipAdress.to_string() << ":" << m_iPort;
    return  ss.str();
  }
protected:
  IPTYPE m_ipAdress;
  int m_iPort;
  bool m_bInvalid;
};

using ess_ip_endpoint4_t = ess_ip_end_point<ess_ip4address>;
using ess_ip_endpoint6_t = ess_ip_end_point<ess_ip6address>;

 #endif
