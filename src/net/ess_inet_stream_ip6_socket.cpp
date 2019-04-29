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


#include "net/ess_inet_stream_ip6_socket.h"


ess_inet_stream_ip6_socket::ess_inet_stream_ip6_socket()
  : ess_inet_ip6_socket(ESS_SOCKET_PROTO_STREAM,
    ESS_SOCKET_PROTO_UNSPEC,  "ess_inet_socket_ip4") { }

ess_inet_stream_ip6_socket::ess_inet_stream_ip6_socket(std::string name)
  : ess_inet_ip6_socket(ESS_SOCKET_PROTO_STREAM,
    ESS_SOCKET_PROTO_UNSPEC, name) { }

<<<<<<< HEAD
<<<<<<< HEAD
ess_error_t ess_inet_stream_ip6_socket::listen(int optons) {
  return ess_socket_listen(m_iSocket, optons);
=======
=======
>>>>>>> 92de4c3f13a31f0e4b5904d64c8040017622b2c8
ess_error_t ess_inet_stream_ip6_socket::listen(ess_ip6address address, int port) {
  return ESS_ERROR_NOT_IMP;
}
ess_error_t ess_inet_stream_ip6_socket::listen(int port) {
  return ESS_ERROR_NOT_IMP;
<<<<<<< HEAD
>>>>>>> 92de4c3f13a31f0e4b5904d64c8040017622b2c8
=======
>>>>>>> 92de4c3f13a31f0e4b5904d64c8040017622b2c8
}
