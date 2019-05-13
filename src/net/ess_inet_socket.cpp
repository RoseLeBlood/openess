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


#include "net/ess_inet_socket.h"
# include <sys/socket.h>
# include <sys/types.h>

ess_inet_socket::ess_inet_socket(ess_socket_fam fam, ess_socket_type socket_type,
  ess_socket_proto_t protocolType)
  : ess_socket(fam, socket_type, protocolType, "ess_inet_socket") {

}

ess_inet_socket::ess_inet_socket(ess_socket_fam fam, ess_socket_type socket_type,
 ess_socket_proto_t protocolType, std::string name)
  : ess_socket(fam, socket_type, protocolType, name) {

}

ess_error_t ess_inet_socket::bind(int port) {
  ess_error_t error = create();
  if(error == ESS_OK)
    error =  ess_socket_bind(m_iSocket, port);
  return error;
}

void ess_inet_socket::set_strem_nodelay(int flag) {
  ess_setsockopt(m_iSocket, IPPROTO_TCP,  (ess_socket_option_name_t)TCP_NODELAY, (char*)&flag, sizeof(int));
}
