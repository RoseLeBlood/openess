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
 * @file ess_inet_stream_ip4_server.h
 * @author Anna Sopdia Schröck
 * @date 18 Februar 2019
 */

#ifndef _ESS_INET_STREAM_IP4_SERVER_H_
#define _ESS_INET_STREAM_IP4_SERVER_H_

#include "ess_inet_stream_ip4_socket.h"
#include "ess_inet_stream_server.h"

class ess_inet_stream_ip4_server : public ess_inet_stream_ip4_socket,
                                                                    ess_inet_stream_server {
public:
  ess_inet_stream_ip4_server();
  ess_inet_stream_ip4_server(std::string name);

  ess_error_t listen(int optons);

  virtual uint32_t write(const void* data, size_t offset, size_t size);
  virtual uint32_t read(void* data, size_t offset, size_t size);

};
#endif
