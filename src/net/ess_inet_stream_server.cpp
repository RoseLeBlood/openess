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
 * @file ess_inet_stream_server.cpp
 * @author Anna Sopdia Schröck
 * @date 26 Februar 20119
 *
 */
#include "net/ess_inet_stream_server.h"

/**
* @brief construct the server socket.
*
* this constructor create zhe server socket for TCP/IP communication.
*
* @param fam The protocol: `ESS_SOCKET_FAMILY_IP4/ESS_SOCKET_FAMILY_IP6`
*/
ess_inet_stream_server::ess_inet_stream_server(ess_socket_fam fam)
  : ess_insocket(fam, ESS_SOCKET_PROTO_STREAM) {

}
/**
 * @brief listen
 * initializes a server socket for TCP/IP communication.
 *
 * @param bindhost The address the server should listen on
 * @param bindport The port the server should listen on
 * @param flags Flags for `socket(2)`
 *
 * @retval ESS_ERROR_ALREADY_CREATED socket allready in use
 * @retval ESS_ERROR_NULL `bindhost` are null or `bindport` < 80
 */
ess_error_t ess_inet_stream_server::listen(const std::string& bindhost, const int bindport, int flags) {
  if ( m_iSocket != -1 ) return ess_error_t::ESS_ERROR_ALREADY_CREATED;
	if ( bindhost.empty() ||  bindport < 80 ) return ess_error_t::ESS_ERROR_NULL;

  m_strHost = bindhost;
	m_iPort = bindport;

  return  ess_socket_server_create(get_family() , get_proto(),
    m_strHost, m_iPort, flags, 0, &m_iSocket);
}


ess_insocket* ess_inet_stream_server::accept(int flags) {
  int client_sfd;
  int port;


	ess_insocket* client = new ess_insocket(get_family(), get_proto());
	std::unique_ptr<char[]> src_host(new char[1024]);


 client_sfd = ess_accept_stream_socket(m_iSocket, src_host.get(), 1023, &port, flags);
 if(client_sfd == -1) {
   if(errno != EWOULDBLOCK ){
     //ESP_LOGE("ESST", "EWOULDBLOCK");
   }
   delete client;
   return nullptr;
 }
 client->m_iSocket = client_sfd;
 client->m_strHost = std::string(src_host.get());
 client->m_iPort = port;

  return client;
}
std::unique_ptr<ess_insocket> ess_inet_stream_server::accept_ex(int flags) {
  return std::unique_ptr<ess_insocket>(accept(flags));
}
