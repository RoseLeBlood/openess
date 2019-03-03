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
 * @file ess_socket.h
 * @author Anna Sopdia Schröck
 * @date 18 Februar 2019
 * @brief Contains ess_socket (base class) and ess_insocket (base for all internet sockets)
 */

#ifndef _ESS_SOCKET_H_
#define _ESS_SOCKET_H_

#include "ess.h"

#include "ess_network.h"

/**
 * @brief socket is the base class of every other ess_socket object.
 */
class ess_socket {
  friend class ess_inet_stream_server;
public:
  ess_socket()  { }
  ess_socket(ess_socket_fam fam, ess_socket_pro proto);
  ess_socket(const ess_socket&) = delete;
  ess_socket(ess_socket&&);

  virtual ~ess_socket();

  virtual ess_error_t destroy(void);

  int set_opt(int level, int optname, const char* optval, unsigned int optlen) const;

  int get_handle(void) const { return m_iSocket;}
  ess_socket_fam_t get_family() { return m_eFam; }
  ess_socket_pro_t get_proto() { return m_eProto; }

  bool is_socket() { return m_iSocket != -1; }
protected:
  ess_socket_fam_t m_eFam;
  ess_socket_pro_t m_eProto;
  int m_iSocket;
};


/**
 * @brief	Internet-socket base class
 * This class provides some fields for all internet sockets, like remote host and port and the used protocol version.
 */

class ess_insocket : public ess_socket {
  friend class ess_inet_stream_server;
public:
  ess_insocket(ess_socket_fam fam, ess_socket_pro proto);

  const std::string& get_host(void) const { return m_strHost; }
  int get_port(void)  { return m_iPort;  }
protected:
  /// The address we're bound or connected to
  std::string m_strHost;
  /// The port we're bound or connected to
 int m_iPort;
};

/**
* @}
*/
#endif
