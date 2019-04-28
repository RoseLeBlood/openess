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

ess_inet_stream_ip4_server::ess_inet_stream_ip4_server()
  : ess_inet_stream_ip4_socket("ess_inet_stream_ip4_server") {

}
ess_inet_stream_ip4_server::ess_inet_stream_ip4_server(std::string name)
  : ess_inet_stream_ip4_socket(name) {

}
ess_error_t ess_inet_stream_ip4_server::listen(int optons) {
  return ess_socket_listen(m_iSocket, optons);
}
uint32_t ess_inet_stream_ip4_server::write(const void* data, size_t offset, size_t size) {

  return 0;
}
uint32_t ess_inet_stream_ip4_server::read(void* data, size_t offset, size_t size) {

  return 0;
}
