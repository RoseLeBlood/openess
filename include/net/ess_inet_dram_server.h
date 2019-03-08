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
 * @file ess_inet_dram_server.h
 * @author Anna Sopdia Schröck
 * @date 19 Februar 2019
 * @brief Contains the inet dram server (UDP Server) socket
 */

#ifndef _ESS_SOCKET_INET_DGRAM_SERVER_H_
#define _ESS_SOCKET_INET_DGRAM_SERVER_H_

#include "net/ess_insocket_dram.h"

/**
* @addtogroup socket
* @{
*/
class ess_inet_dram_server : public ess_insocket_dram{
public:
  ess_inet_dram_server(const std::string& host, const int port, ess_socket_fam fam, bool lite);

  virtual ess_error_t bind(int flags = 0);

private:
  bool m_bLite;
};

class ess_inet_dram_server_ip4 : public ess_inet_dram_server {
public:
  ess_inet_dram_server_ip4(const std::string& host,const int port);
};
class ess_inet_dramlite_server_ip4 : public ess_inet_dram_server {
public:
  ess_inet_dramlite_server_ip4(const std::string& host,const int port);
};


class ess_inet_dram_server_ip6 : public ess_inet_dram_server {
public:
  ess_inet_dram_server_ip6(const std::string& host,const int port);
};
class ess_inet_dramlite_server_ip6 : public ess_inet_dram_server {
public:
  ess_inet_dramlite_server_ip6(const std::string& host,const int port);
};
/**
* @}
*/
#endif
