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
 * @file ess_network.cpp
 * @author Anna Sopdia Schröck
 * @date 20 Februar 2019
 * @brief  platform specific socket functions for all platforms
 *
 */
#include "net/ess_network.h"

# include <sys/socket.h>
# include <sys/types.h>

/**
  * @brief convert ess_socket_fam to socket type (AF_)
  * @code
  * // AF_TYPE == AF_INET
  * int AF_TYPE = ess_socket_fam2platform(ESS_SOCKET_FAMILY_IP4);
  * @endcode
  * @param [in] fam the ess_socket_fam enum member
  * @return the socket family type
  * @retval -1 socket family don't avaible on this platform
*/
int ess_socket_fam2platform(ess_socket_fam fam) {
  switch ( fam ) {
    case ESS_SOCKET_FAMILY_IP4 : return AF_INET;
    case ESS_SOCKET_FAMILY_IP6 : return AF_INET6;
    case ESS_SOCKET_FAMILY_BOTH: return AF_UNSPEC;
    #if  ESS_PLATFORM_ESP32 == 0
    case ESS_SOCKET_FAMILY_X25: return AF_X25;
    case ESS_SOCKET_FAMILY_AX25: return AF_AX25;
    case ESS_SOCKET_FAMILY_IPX: return AF_IPX;
    case ESS_SOCKET_FAMILY_NETLINK: return AF_NETLINK;
    case ESS_SOCKET_FAMILY_ATMPVC: return AF_ATMPVC;
    case ESS_SOCKET_FAMILY_APPLETALK: return AF_APPLETALK;
    case ESS_SOCKET_FAMILY_PACKET: return AF_PACKET;
    case ESS_SOCKET_FAMILY_ALG: return AF_ALG;
    #endif
    default:  return -1;
  }
  return -1;
}

/**
  * @brief convert ess_socket_pro to socket type (SOCK_)
  * @code
  * // SOCK_TYPE == SOCK_RAW
  * int SOCK_TYPE = ess_socket_pro2platform(ESS_SOCKET_PROTO_RAW);
  * @endcode
  * @param [in] fam the ess_socket_fam enum member
  * @return the socket family type
  * @retval -1 socket proto don't avaible on this platform
*/
int ess_socket_pro2platform(ess_socket_pro proto) {
  switch (proto) {
    case ESS_SOCKET_PROTO_DRAM:        return SOCK_DGRAM;
    case ESS_SOCKET_PROTO_STREAM: return SOCK_STREAM;
    case ESS_SOCKET_PROTO_DRAM_LITE: return SOCK_DGRAM;
    case ESS_SOCKET_PROTO_RAW: return SOCK_RAW;
    #if  ESS_PLATFORM_ESP32 == 0
    case ESS_SOCKET_PROTO_SEQPACKET: return SOCK_SEQPACKET;
    case ESS_SOCKET_PROTO_RDM: return SOCK_RDM;
    #endif
    default:
     return -1;
  }

  return -1;
}

std::string ess_socket_fam2string(ess_socket_fam fam){
  switch ( fam ) {
    case ESS_SOCKET_FAMILY_IP4 : return "ESS_SOCKET_FAMILY_IP4";
    case ESS_SOCKET_FAMILY_IP6 : return "ESS_SOCKET_FAMILY_IP6";
    case ESS_SOCKET_FAMILY_BOTH: return "ESS_SOCKET_FAMILY_BOTH";
    case ESS_SOCKET_FAMILY_X25: return "ESS_SOCKET_FAMILY_X25";
    case ESS_SOCKET_FAMILY_AX25: return "ESS_SOCKET_FAMILY_AX25";
    case ESS_SOCKET_FAMILY_IPX: return "ESS_SOCKET_FAMILY_IPX";
    case ESS_SOCKET_FAMILY_NETLINK: return "ESS_SOCKET_FAMILY_NETLINK";
    case ESS_SOCKET_FAMILY_ATMPVC: return "ESS_SOCKET_FAMILY_ATMPVC";
    case ESS_SOCKET_FAMILY_APPLETALK: return "ESS_SOCKET_FAMILY_APPLETALK";
    case ESS_SOCKET_FAMILY_PACKET: return "ESS_SOCKET_FAMILY_PACKET";
    case ESS_SOCKET_FAMILY_ALG: return "ESS_SOCKET_FAMILY_ALG";
  }
  return "ESS_SOCKET_FAMILY_MAX";
}
std::string ess_socket_pro2string(ess_socket_pro proto) {
  switch (proto) {
    case ESS_SOCKET_PROTO_DRAM:        return "ESS_SOCKET_PROTO_DRAM";
    case ESS_SOCKET_PROTO_STREAM: return "ESS_SOCKET_PROTO_STREAM";
    case ESS_SOCKET_PROTO_DRAM_LITE: return "ESS_SOCKET_PROTO_DRAM_LITE";
    case ESS_SOCKET_PROTO_RAW: return "ESS_SOCKET_PROTO_RAW";
    case ESS_SOCKET_PROTO_SEQPACKET: return "ESS_SOCKET_PROTO_SEQPACKET";
    case ESS_SOCKET_PROTO_RDM: return "ESS_SOCKET_PROTO_RDM";
  }
  return "ESS_SOCKET_PROTO_MAX";
}
