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
 * @file ess_inet_ip4_socket.h
 * @author Anna Sopdia Schröck
 * @date 18 Februar 2019
 */

 #ifndef _ESS_INET_SOCKET_IP4_H_
 #define _ESS_INET_SOCKET_IP4_H_

#include "ess_inet_socket.h"

class ess_inet_ip4_socket : public ess_inet_socket {
public:
  ess_inet_ip4_socket(ess_socket_type socket_type,
    ess_socket_proto_t protocolType);

  ess_inet_ip4_socket(ess_socket_type socket_type,
    ess_socket_proto_t protocolType, std::string name);
};

#endif
