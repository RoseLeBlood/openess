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
 * @file ess_network.h
 * @author Anna Sopdia Schröck
 * @date 20 Februar 2019
 * @brief  platform specific socket functions
 *
 */
#ifndef _ESS_PLATFORM_NETWORK_H_
#define _ESS_PLATFORM_NETWORK_H_

#include "ess.h"

/**
* @addtogroup socket
* @{
*/
/**
 * @brief which ip family are use
 */
typedef enum ess_socket_fam {
  ESS_SOCKET_FAMILY_IP4,       /**< Internet protocol version 4 */
  ESS_SOCKET_FAMILY_IP6,      /**< Internet protocol version 6 */
  ESS_SOCKET_FAMILY_BOTH,   /**< Unspec DNS resolver should decide.*/
  ESS_SOCKET_FAMILY_X25, /** < x25 - ITU-T X.25 / ISO-8208 protocol interface not avaible on esp32*/
  ESS_SOCKET_FAMILY_NETLINK, /**< communication between kernel and user space  not avaible on esp32*/
  ESS_SOCKET_FAMILY_AX25,  /**< Amateur radio AX.25 protocol  not avaible on esp32*/
  ESS_SOCKET_FAMILY_IPX,  /**< IPX - Novell protocols  not avaible on esp32*/
  ESS_SOCKET_FAMILY_ATMPVC,           /**< Access to raw ATM PVCs not avaible on esp32*/
  ESS_SOCKET_FAMILY_APPLETALK,        /**< AppleTalk                       not avaible on esp32*/
  ESS_SOCKET_FAMILY_PACKET,          /**< Low level packet interface      not avaible on esp32*/
  ESS_SOCKET_FAMILY_ALG,              /**< Interface to kernel crypto API not avaible on esp32*/
}ess_socket_fam_t;



/**
 * @brief which comunications protocol are use
 */
typedef enum ess_socket_type {
  ESS_SOCKET_PROTO_DRAM,              /**<  Supports datagrams (connectionless, unreliable messages  of a fixed maximum length). */
  ESS_SOCKET_PROTO_STREAM,         /**< Provides sequenced, reliable, two-way, connection-based
                                                                              byte  streams.  An out-of-band data transmission mecha‐
                                                                              nism may be supported.  */

  ESS_SOCKET_PROTO_RAW,        /**<Provides raw network protocol access. */
  ESS_SOCKET_PROTO_RDM,       /**< Provides a reliable datagram layer that does not  guarantee ordering. not avaible on esp32*/
  ESS_SOCKET_PROTO_SEQPACKET, /**<Provides  a  sequenced,  reliable,  two-way connection based data transmission path  for  datagrams  of  fixed
                                                                            maximum  length;  a  consumer  is  required  to read an
                                                                            entire packet with each input system call. not avaible on esp32*/

}ess_socket_type_t;

typedef enum ess_socket_proto {
      ESS_SOCKET_PROTO_UNSPEC = 0,
      ESS_SOCKET_PROTO_UDPLITE = 136,
} ess_socket_proto_t;

typedef enum  ess_socket_option_name {
  ESS_SOCKET_OPTION_DEBUG = 0x0001,
  ESS_SOCKET_OPTION_ACCEPTCONN = 0x0002,
  ESS_SOCKET_OPTION_BROADCAST = 0x0020,
  ESS_SOCKET_OPTION_REUSEADDR = 0x0004,
  ESS_SOCKET_OPTION_KEEPALIVE = 0x0008,
  ESS_SOCKET_OPTION_LINGER = 0x0080,
  ESS_SOCKET_OPTION_OOBINLINE = 0x0100,
  ESS_SOCKET_OPTION_SNDBUF = 0x1001,
  ESS_SOCKET_OPTION_RCVBUF = 0x1002,
  ESS_SOCKET_OPTION_ERROR = 0x1007,
  ESS_SOCKET_OPTION_TYPE = 0x1008,
  ESS_SOCKET_OPTION_DONTROUTE = 0x0010,
  ESS_SOCKET_OPTION_RCVLOWAT = 0x1004,
  ESS_SOCKET_OPTION_RCVTIMEO = 0x1006,
  ESS_SOCKET_OPTION_SNDLOWAT = 0x1003,
  ESS_SOCKET_OPTION_SNDTIMEO = 0x1005,
}ess_socket_option_name_t;

int ess_socket_fam2platform(ess_socket_fam fam); // ess_network.cpp
int ess_socket_type2platform(ess_socket_type proto); // ess_network.cpp

std::string ess_socket_fam2string(ess_socket_fam fam); // ess_network.cpp
std::string ess_socket_type2string(ess_socket_type proto); // ess_network.cpp


int ess_socket(ess_socket_fam fam, ess_socket_type type, ess_socket_proto protocolType);
ess_error_t ess_socket_close(int socket);

int ess_setsockopt(int socket, int level, ess_socket_option_name_t optname,
  const char* optval, unsigned int optlen);

int ess_getsockopt(int socket, int level, ess_socket_option_name_t optname,
   const char* optval, unsigned int* optlen);


ess_error_t ess_socket_bind(int socket,  int port);

ess_error_t ess_socket_listen(int socket, int options) ;

#endif
