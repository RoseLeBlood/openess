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
 * @file ess_insocket_dram.cpp
 * @author Anna Sopdia Schröck
 * @date 18 Februar 20119
 * @brief Contains the inet_dgram class
 */
#include "ess_insocket_dram.h"

# include <stdlib.h>
# include <stdio.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <unistd.h> // read()/write()
# include <stdint.h>
# include <netdb.h> // getaddrinfo()
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <netinet/in.h>

# include <iostream>
# include <string>
# include <string.h>
# include <memory>

/**
 * @brief Receives data from peer
 *
 * rcvfrom is the equivalent to `recvfrom(2)`.
 *
 * @param buf Target memory
 * @param len The size of the target memory
 * @retval >0 n bytes of data were read into `buf`.
 * @retval 0 Peer sent EOF
 * @retval -1 Socket is non-blocking and returned without any data.
 */
unsigned int ess_insocket_dram::read(void* buf, unsigned int len) {
  struct sockaddr_storage client;
  if ( m_iSocket == -1 ) { return -1; }
  if ( buf == NULL || len == 0) return -1;

  memset(buf,0,len);

  socklen_t stor_addrlen = sizeof(struct sockaddr_storage);

  return recvfrom(m_iSocket,buf,len,0,(struct sockaddr*)&client,&stor_addrlen);
}
/**
 * @brief rcvfrom for C++ strings, implemented consistently
 *
 * rcvfrom is the equivalent to `recvfrom(2)`.
 *
 * @param buf The string where the received data should be stored at. (auto resize)
 * @retval >0 n bytes of data were read into `buf`.
 * @retval 0 Peer sent EOF
 * @retval -1 Socket is non-blocking and returned without any data.
 */
unsigned int ess_insocket_dram::read(std::string& buf) {
  unsigned int bytes;

  using std::unique_ptr;
  std::unique_ptr<char[]> cbuf(new char[buf.size()]);

  memset(cbuf.get(),0,buf.size());

  bytes = read(cbuf.get(),static_cast<size_t>(buf.size()));

  buf.resize(bytes);
  buf.assign(cbuf.get(), bytes);

  return bytes;
}
unsigned int ess_insocket_dram::write(const void* buf, size_t len, const char* dsthost, const char* dstport) {
  struct sockaddr_storage oldsock;
  struct addrinfo *result, *result_check, hint;
  socklen_t oldsocklen = sizeof(struct sockaddr_storage);
  int return_value;

  if ( m_iSocket == -1 ) { return -1; }

  if (  getsockname(m_iSocket,(struct sockaddr*)&oldsock,(socklen_t*)&oldsocklen) == -1)  return -1;
  memset(&hint,0,sizeof(struct addrinfo));

  hint.ai_family = oldsock.ss_family;
  hint.ai_socktype = SOCK_DGRAM;

  if (  getaddrinfo(dsthost, dstport, &hint, &result) != 0 ) return -1;

  for ( result_check = result; result_check != NULL; result_check = result_check->ai_next )  {

    return_value =  sendto(m_iSocket, buf, len, 0, result_check->ai_addr, result_check->ai_addrlen);

    if(return_value != -1) break;
  }
  freeaddrinfo(result);
  return return_value;
}
/**
 * @brief Send data to UDP peer
 *
 * This is the counterpart to system's `sendto(2)`. It sends data to a UDP peer.
 *
 * @param buf The data to be sent
 * @param dsthost Target host
 * @param dstport Target port
 *
 * @retval -1 Socket is non-blocking and didn't send any data.
 */
unsigned int ess_insocket_dram::write(const std::string& buf, const std::string& dsthost, const std::string& dstport) {
  ssize_t bytes;
  bytes = write(buf.c_str(), buf.size(), dsthost.c_str(), dstport.c_str());
  return bytes;
}
