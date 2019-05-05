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
 * @file ess_inet_socket.h
 * @author Anna Sopdia Schröck
 * @date 18 Februar 2019
 */

 #ifndef _ESS_INET_SOCKET_H_
 #define _ESS_INET_SOCKET_H_

 #include "ess_socket.h"

 class ess_inet_socket : public ess_socket {
 public:
   ess_inet_socket(ess_socket_fam fam, ess_socket_type socket_type,
     ess_socket_proto_t protocolType);

   ess_inet_socket(ess_socket_fam fam, ess_socket_type socket_type,
       ess_socket_proto_t protocolType, std::string name);

   ess_error_t bind(int port);

   virtual uint32_t write(const void* data, size_t offset, size_t size);
   virtual uint32_t read(void* data, size_t offset, size_t size);

   virtual uint32_t write_string(std::string srt);

   void set_strem_nodelay(int flag);
 private:
   int m_iPort;
};


#endif
