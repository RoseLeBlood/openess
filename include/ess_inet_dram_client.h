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
 * @file ess_inet_dram_client.h
 * @author Anna Sopdia Schröck
 * @date 19 Februar 20119
 * @brief Contains the inet dram client (UDP client) socket
 */

#ifndef _ESS_SOCKET_INET_DGRAM_CLIENT_H_
#define _ESS_SOCKET_INET_DGRAM_CLIENT_H_

#include "ess_insocket_dram.h"

/**
* @addtogroup ess_socket (SAL)
* @{
*/

class ess_inet_dram_client : public ess_insocket_dram {
  friend ess_inet_dram_client& operator<<(ess_inet_dram_client& sock, const char* str);
  friend ess_inet_dram_client& operator<<(ess_inet_dram_client& sock, const std::string& str);

  friend ess_inet_dram_client& operator>>(ess_inet_dram_client& sock, std::string& dest);
  friend ess_inet_dram_client& operator>>(ess_inet_dram_client& sock, char* dest);
public:
  ess_inet_dram_client(ess_socket_fam fam) : ess_inet_dram_client(fam, 0, false) { }
  ess_inet_dram_client(ess_socket_fam fam, int flags) : ess_inet_dram_client(fam, flags, false) { }
  ess_inet_dram_client(ess_socket_fam fam, int flags, bool lite); //

  ess_error_t connect(const std::string& dsthost, const std::string& dstport); //
  ess_error_t disconnect(void); //

  unsigned int write(const void* buf, unsigned int len, int flags=0);
	unsigned int read(void* buf, unsigned int len, int flags=0);

  /**
   * @brief if the socket connected
   * @retval true the socket is connected
   * @reval false the socket is not connected
   */
  bool is_connected(void) const { return m_isConnected; }
private:
  bool m_isConnected;
};

class ess_inet_dram_client_ip4 : public ess_inet_dram_client {
public:
  ess_inet_dram_client_ip4()
    : ess_inet_dram_client(ESS_SOCKET_FAMILY_IP4, 0)  { }
  ess_inet_dram_client_ip4(int flags)
    : ess_inet_dram_client(ESS_SOCKET_FAMILY_IP4, flags)  { }
};


class ess_inet_dram_client_ip6 : public ess_inet_dram_client {
public:
  ess_inet_dram_client_ip6()
    : ess_inet_dram_client(ESS_SOCKET_FAMILY_IP6, 0)  { }
  ess_inet_dram_client_ip6(int flags)
    : ess_inet_dram_client(ESS_SOCKET_FAMILY_IP6, flags)  { }
};
/**
* @}
*/
#endif
