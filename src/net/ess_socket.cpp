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



/**
 * @brief Constructor
 *
 */
ess_socket::ess_socket(ess_socket_fam fam, ess_socket_type socket_type,
  ess_socket_proto protocolType, std::string name)
   : ess_object(name) {

   m_eFam = fam;
   m_eProto = protocolType;
   m_fType = socket_type;
}

/**
 * @brief Destructor: closes socket.
 */
ess_socket::~ess_socket(void) {
    destroy();
}
ess_error_t ess_socket::create() {
  if ( 0 > m_iSocket ) return ESS_ERROR_NULL;
  m_iSocket = ::ess_socket(m_eFam, m_fType, m_eProto);
  return m_iSocket != -1 ? ESS_OK : ESS_ERROR;
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
    if(ess_socket_close(m_iSocket) != ESS_OK) return ESS_ERROR_CLOSE;
    m_iSocket = -1;
    return ESS_OK;
}

int ess_socket::set_opt(int level, ess_socket_option_name_t optname,
  const char* optval, unsigned int optlen) const {
    return ess_setsockopt(m_iSocket, level, optname, optval, optlen);
}
int ess_socket::get_opt(int level, ess_socket_option_name_t optname,
  char* optval, unsigned int *option_len) {
  return ess_getsockopt(m_iSocket, level, optname, optval, option_len);
}
