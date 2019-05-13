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


#include "net/ess_inet_stream_ip4_server.h"
#include "net/ess_server_stream.h"

ess_inet_stream_ip4_server::ess_inet_stream_ip4_server()
  : ess_inet_stream_server("ess_inet_stream_ip4_server") {
    m_iAccetpedHandle = -1;
}
ess_inet_stream_ip4_server::ess_inet_stream_ip4_server(std::string name)
  : ess_inet_stream_server(name) {
    m_iAccetpedHandle = -1;
}
ess_error_t ess_inet_stream_ip4_server::listen(int port, int max_clients) {
  if(m_bIsListing)
    return ESS_ERROR;

  ess_error_t error;
  if( (error = m_ip4Socket.bind(port) ) != ESS_OK) return error;
  m_ip4Socket.set_strem_nodelay(1);

  error =  ess_socket_listen(m_ip4Socket.get_handle(), max_clients);
  m_bIsListing = (error == ESS_OK);
  m_iAccetpedHandle = -1;
  return error;
}
bool ess_inet_stream_ip4_server::client_available() {
  if (m_iAccetpedHandle >= 0)  return true;

  ess_socket_accept(m_ip4Socket.get_handle(),  &m_iAccetpedHandle);
  return  (m_iAccetpedHandle >= 0) ;
}
ess_inet_stream_ip4_client ess_inet_stream_ip4_server::get_client() {
  int client_sock = -1;
  int val = 1;

  if(!m_bIsListing)
    return ess_inet_stream_ip4_client();

  if (m_iAccetpedHandle <= 0) {
    ess_socket_accept(m_ip4Socket.get_handle(),  &client_sock);
  } else {
    client_sock = m_iAccetpedHandle;
    m_iAccetpedHandle = -1;
  }

  if(client_sock >= 0) {
    if(ess_setsockopt(client_sock, SOL_SOCKET, (ess_socket_option_name_t)SO_KEEPALIVE, (char*)&val, sizeof(int)) != 0)
      return ess_inet_stream_ip4_client();

    if(ess_setsockopt(client_sock, IPPROTO_TCP, (ess_socket_option_name_t)TCP_NODELAY, (char*)&val, sizeof(int)) == 0)
      return ess_inet_stream_ip4_client(client_sock);
  }
  return ess_inet_stream_ip4_client();
}
ess_error_t ess_inet_stream_ip4_server::stop() {
  if(!m_bIsListing) return ESS_ERROR;
  return m_ip4Socket.destroy();
}
 ess_ip_end_point ess_inet_stream_ip4_server::get_end_point()  {
   return ess_ip_end_point( ESS_IP4ADRESS_ANY, m_ip4Socket.get_port() );
 }
