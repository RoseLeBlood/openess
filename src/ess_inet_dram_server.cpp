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
 * @brief Create datagram (udp) socket and bind it.
 *
 * @param host Bind address (Wildcard: "0.0.0.0"/"::")
 * @param port Bind port
 * @param ess_socket_fam `ESS_SOCKET_FAMILY_IP4` or `ESS_SOCKET_FAMILY_IP6` or `ESS_SOCKET_FAMILY_BOTH`
 * @param lite if true then create a dram lite socket
 */
ess_inet_dram_server::ess_inet_dram_server(std::string host, std::string port, ess_socket_fam fam, bool lite)
  : ess_insocket_dram(fam) {
  m_iSocket = setup(host,port,0, lite);
}
/**
 * @brief Create datagram (udp) socket and bind it.
 *
 * @param host Bind address (Wildcard: "0.0.0.0"/"::")
 * @param port Bind port
 * @param ess_socket_fam `ESS_SOCKET_FAMILY_IP4` or `ESS_SOCKET_FAMILY_IP6` or `ESS_SOCKET_FAMILY_BOTH`
 * @param flags Flags for `socket(2)`
 * @param lite if true then create a dram lite socket
 */
ess_inet_dram_server::ess_inet_dram_server(std::string host, std::string port, ess_socket_fam fam, int flags, bool lite)
  : ess_insocket_dram(fam) {
 m_iSocket = setup(host,port,flags, lite);
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
int ess_inet_dram_server::setup(std::string host, std::string port, int flags, bool lite) {
  if ( host.c_str() == NULL || port.c_str() == NULL ) return -1;

  int retval;
  struct addrinfo *result, *result_check, hints;

  memset(&hints,0,sizeof(struct addrinfo));
  hints.ai_socktype = SOCK_DGRAM;

  switch ( get_family() ) {
    case ESS_SOCKET_FAMILY_IP4: hints.ai_family = AF_INET; break;
    case ESS_SOCKET_FAMILY_IP6:   hints.ai_family = AF_INET6; break;
    case ESS_SOCKET_FAMILY_BOTH: hints.ai_family = AF_UNSPEC; break;
default:
    return -1;
  }
  hints.ai_flags = AI_PASSIVE;
  hints.ai_protocol =  lite ? IPPROTO_UDPLITE : 0;
  if ( getaddrinfo( m_strHost.c_str(), m_strPort.c_str(), &hints, &result )  !=0  ) {
    return -1;
  }

  for ( result_check = result; result_check != NULL; result_check = result_check->ai_next )  {
    m_iSocket = socket( result_check->ai_family, result_check->ai_socktype | flags, result_check->ai_protocol  );
    if ( m_iSocket < 0 )  continue;

    retval = bind(m_iSocket, result_check->ai_addr, (socklen_t)result_check->ai_addrlen );
    if ( retval != 0 )  { close(m_iSocket); continue;   } else { break; } // Only on UDP break here

    /* // On TCP  (Sstream)
  	    retval = listen(sfd,LIBSOCKET_BACKLOG);
        if ( retval != 0 )  { close(m_iSocket); continue;   } else { break; }
          }*/
  }
  if ( result_check == NULL )  m_iSocket = -1;

  freeaddrinfo(result);

  m_strHost = host;
  m_strPort = port;

  return m_iSocket;
}

/**
 * @brief Create datagram (udp)  IP4 socket and bind it.
 *
 * @param host Bind address (Wildcard: "0.0.0.0")
 * @param port Bind port
 */
ess_inet_dram_server_ip4::ess_inet_dram_server_ip4(std::string host, std::string port, bool lite)
  : ess_inet_dram_server(host, port, ESS_SOCKET_FAMILY_IP4, lite) { }
/**
 * @brief Create datagram (udp)  IP4 socket and bind it.
 *
 * @param host Bind address (Wildcard: "0.0.0.0")
 * @param port Bind port
 * @param flags Flags for `socket(2)`
 */
ess_inet_dram_server_ip4::ess_inet_dram_server_ip4(std::string host, std::string port, int flags, bool lite)
  : ess_inet_dram_server(host, port, ESS_SOCKET_FAMILY_IP4, flags, lite) { }


/**
 * @brief Create datagram (udp)  IP6 socket and bind it.
 *
 * @param host Bind address (Wildcard: "::")
 * @param port Bind port
 */
ess_inet_dram_server_ip6::ess_inet_dram_server_ip6(std::string host, std::string port, bool lite)
  : ess_inet_dram_server(host, port, ESS_SOCKET_FAMILY_IP6, lite) { }
/**
 * @brief Create datagram (udp)  IP6 socket and bind it.
 *
 * @param host Bind address (Wildcard: "::")
 * @param port Bind port
 * @param flags Flags for `socket(2)`
 */
ess_inet_dram_server_ip6::ess_inet_dram_server_ip6(std::string host, std::string port, int flags, bool lite)
  : ess_inet_dram_server(host, port, ESS_SOCKET_FAMILY_IP6, flags, lite) { }
