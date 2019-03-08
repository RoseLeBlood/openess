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
 * @file ess_socket.cpp
 * @author Anna Sopdia Schröck
 * @date 18 Februar 2019
 * @brief Contains ess_socket (base class) and ess_insocket (base for all internet sockets)
 */

#include "net/ess_socket.h"
#include "esp_log.h"

#include "config.h"

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

/**
 * @brief Constructor. Sets `m_iSocket` to -1.
 *
 */
ess_socket::ess_socket(ess_socket_fam fam, ess_socket_pro proto) {
   m_eFam = fam;
   m_eProto = proto;
   m_iSocket = -1;
}
/**
 * @brief Move constructor.
 */
ess_socket::ess_socket(ess_socket&& other) {
  m_eFam = other.m_eFam;
  m_eProto = other.m_eProto;
  m_iSocket = other.m_iSocket;
  other.m_iSocket = -1;
}

/**
 * @brief Destructor: closes socket.
 */
ess_socket::~ess_socket(void) {
    destroy();
}
/**
 * @brief	Destroys a socket.
 *
 * @retval ESS_OK    Fine!
 * @retval ESS_ERROR_CLOSE  Most likely the socket was already closed before.
 * @retval ESS_ERROR_NULL  socket not created
 */
ess_error_t ess_socket::destroy(void) {
    if ( 0 > m_iSocket ) return ESS_ERROR_NULL;
    if ( 0 > close(m_iSocket)) return ESS_ERROR_CLOSE;

    m_iSocket = -1;
    return ESS_OK;
}

int ess_socket::set_opt(int level, int optname, const char* optval, unsigned int optlen) const {
    return ess_setsockopt(m_iSocket, level, optname, optval, optlen);
}


ess_insocket::ess_insocket(ess_socket_fam fam, ess_socket_pro proto)
  : ess_socket(fam, proto) {
    m_strHost = "";
    m_iPort = -1;
}
