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
 * @date 18 Februar 20119
 * @brief Contains ess_socket (base class) and ess_insocket (base for all internet sockets)
 */

#ifndef _ESS_SOCKET_H_
#define _ESS_SOCKET_H_

#include "ess.h"

/**
 * @brief which ip family are use
 */
typedef enum ess_socket_fam {
  ESS_SOCKET_FAMILY_IP4,       /**< Internet protocol version 4 */
  ESS_SOCKET_FAMILY_IP6,      /**< Internet protocol version 6 */
  ESS_SOCKET_FAMILY_BOTH   /**< Unspec DNS resolver should decide.*/
}ess_socket_fam_t;

/**
 * @brief which comunications protocol are use
 */
typedef enum ess_socket_pro {
  ESS_SOCKET_PROTO_DRAM,              /**< UDP */
  ESS_SOCKET_PROTO_STREAM,         /**< TCP */
  ESS_SOCKET_PROTO_DRAM_LITE, /**< UDP Lite */
}ess_socket_pro_t;

/**
 * @brief ess_socket status
 */
typedef enum ess_socket_status {
  ESS_SOCKET_STATUS_CREATED,    /**< Socket is created and ready for using */
  ESS_SOCKET_STATUS_LISTEN,         /**< server is running */
  ESS_SOCKET_STATUS_STOPPED,    /**< socket is close*/
  ESS_SOCKET_STATUS_ERROR,       /**< socket has an error */
  ESS_SOCKET_STATUS_DESTROY   /**< socket is destroyed */
}ess_socket_status_t;

/**
 * @brief socket is the base class of every other ess_socket object.
 */
class ess_socket {
public:
  ess_socket() : ess_socket(ESS_SOCKET_FAMILY_IP4, ESS_SOCKET_PROTO_DRAM) { }
  ess_socket(ess_socket_pro proto) : ess_socket(ESS_SOCKET_FAMILY_IP4, proto) { }
  ess_socket(ess_socket_fam fam, ess_socket_pro proto);
  ess_socket(const ess_socket&) = delete;
  ess_socket(ess_socket&&);

  virtual ~ess_socket();

  virtual ess_error_t destroy(void);

  int set_opt(int level, int optname, const char* optval, unsigned int optlen) const;

  int get_handle(void) const { return m_iSocket;}
  ess_socket_fam_t get_family() { return m_eFam; }
  ess_socket_pro_t get_proto() { return m_eProto; }
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
public:
  ess_insocket() : ess_insocket(ESS_SOCKET_FAMILY_IP4, ESS_SOCKET_PROTO_DRAM) { }
  ess_insocket(ess_socket_pro proto) : ess_insocket(ESS_SOCKET_FAMILY_IP4, proto) { }
  ess_insocket(ess_socket_fam fam, ess_socket_pro proto);

  const std::string& get_host(void) const { return m_strHost; }
  const std::string& get_port(void) const { return m_strPort; }
protected:
  /// The address we're bound or connected to
  std::string m_strHost;
  /// The port we're bound or connected to
  std::string m_strPort;
};
#endif
