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
 * @file ess_inet_dram_server.cpp
 * @author Anna Sopdia Schröck
 * @date 19 Februar 2019
 * @brief Contains the inet dram server (UDP Server) socket
 */
#include "ess_inet_dram_server.h"

# include <stdlib.h>
# include <stdio.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <stdint.h>
# include <netdb.h> // getaddrinfo()
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <netinet/in.h> // e.g. struct sockaddr_in on OpenBSD

/**
 * @brief Create datagram (udp) socket
 *
 * @param host Bind address (Wildcard: "0.0.0.0"/"::")
 * @param port Bind port
 * @param ess_socket_fam `ESS_SOCKET_FAMILY_IP4` or `ESS_SOCKET_FAMILY_IP6` or `ESS_SOCKET_FAMILY_BOTH`
 * @param lite if true then create a dram lite socket
 */
ess_inet_dram_server::ess_inet_dram_server(std::string host, std::string port, ess_socket_fam fam, bool lite)
  : ess_insocket_dram(fam, lite ? ESS_SOCKET_PROTO_DRAM_LITE : ESS_SOCKET_PROTO_DRAM) {

    m_strHost = host;
    m_strPort = port;
}

ess_error_t ess_inet_dram_server::bind(int flags) {
  return  ess_socket_server_create(get_family() , get_proto(),
    m_strHost, m_strPort, flags, 0, &m_iSocket);
  //return m_iSocket;
}
/**
 * @brief Set up socket
 *
 * @param host Bind address (Wildcard: "0.0.0.0"/"::")
 * @param port Bind port
 * @param flags Flags for `socket(2)`
 * @param lite if true then create a dram lite socket
 * @return the socket handle
 * @retval <=-1 error
* @retval >0 socket bind ok
 */


/**
 * @brief Create datagram (udp)  IP4 socket and bind it.
 *
 * @param host Bind address (Wildcard: "0.0.0.0")
 * @param port Bind port
 */
ess_inet_dram_server_ip4::ess_inet_dram_server_ip4(std::string host, std::string port, bool lite)
  : ess_inet_dram_server(host, port, ESS_SOCKET_FAMILY_IP4, lite) { }


/**
 * @brief Create datagram (udp)  IP6 socket and bind it.
 *
 * @param host Bind address (Wildcard: "::")
 * @param port Bind port
 */
ess_inet_dram_server_ip6::ess_inet_dram_server_ip6(std::string host, std::string port, bool lite)
  : ess_inet_dram_server(host, port, ESS_SOCKET_FAMILY_IP6, lite) { }
