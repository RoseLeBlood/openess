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


#include "net/ess_inet_ip4_socket.h"

ess_inet_ip4_socket::ess_inet_ip4_socket(ess_socket_type socket_type, ess_socket_proto_t protocolType)
  : ess_inet_socket(ESS_SOCKET_FAMILY_IP4, socket_type, protocolType, "ess_inet_socket_ip6") { }

ess_inet_ip4_socket::ess_inet_ip4_socket(ess_socket_type socket_type,
    ess_socket_proto_t protocolType, std::string name)
    : ess_inet_socket(ESS_SOCKET_FAMILY_IP4, socket_type, protocolType, name) { }
