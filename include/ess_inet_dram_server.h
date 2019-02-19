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
 * @date 19 Februar 20119
 * @brief Contains the inet dram server (UDP Server) socket
 */

#ifndef _ESS_SOCKET_INET_DGRAM_SERVER_H_
#define _ESS_SOCKET_INET_DGRAM_SERVER_H_

#include "ess_insocket_dram.h"

/**
* @addtogroup ess_socket (SAL)
* @{
*/
class ess_inet_dram_server : public ess_insocket_dram{
public:
  ess_inet_dram_server(std::string host, std::string port, ess_socket_fam fam);
  ess_inet_dram_server(std::string host, std::string port, ess_socket_fam fam, int flags);

private:
  virtual int setup(std::string host, std::string port, int flags=0);
};

class ess_inet_dram_server_ip4 : public ess_inet_dram_server {
public:
  ess_inet_dram_server_ip4(std::string host, std::string port);
  ess_inet_dram_server_ip4(std::string host, std::string port, int flags);
};


class ess_inet_dram_server_ip6 : public ess_inet_dram_server {
public:
  ess_inet_dram_server_ip6(std::string host, std::string port);
  ess_inet_dram_server_ip6(std::string host, std::string port, int flags);
};
/**
* @}
*/
#endif
