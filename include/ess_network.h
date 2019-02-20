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
typedef enum ess_socket_pro {
  ESS_SOCKET_PROTO_DRAM,              /**<  Supports datagrams (connectionless, unreliable messages  of a fixed maximum length). */
  ESS_SOCKET_PROTO_STREAM,         /**< Provides sequenced, reliable, two-way, connection-based
                                                                              byte  streams.  An out-of-band data transmission mecha‐
                                                                              nism may be supported.  */
  ESS_SOCKET_PROTO_DRAM_LITE, /**< Lightweight User Datagram Protocol */


  ESS_SOCKET_PROTO_RAW,        /**<Provides raw network protocol access. */
  ESS_SOCKET_PROTO_RDM,       /**< Provides a reliable datagram layer that does not  guarantee ordering. not avaible on esp32*/
  ESS_SOCKET_PROTO_SEQPACKET, /**<Provides  a  sequenced,  reliable,  two-way connection based data transmission path  for  datagrams  of  fixed
                                                                            maximum  length;  a  consumer  is  required  to read an
                                                                            entire packet with each input system call. not avaible on esp32*/

}ess_socket_pro_t;


int ess_socket_fam2platform(ess_socket_fam fam); // ess_network.cpp
int ess_socket_pro2platform(ess_socket_pro proto); // ess_network.cpp

std::string ess_socket_fam2string(ess_socket_fam fam); // ess_network.cpp
std::string ess_socket_pro2string(ess_socket_pro proto); // ess_network.cpp

/**
 * @brief create the specific platform socket handle
 *
 *
 * @param fam which ip family are use
 * @param proto which comunications protocol are use
 * @param flags Flags for `socket(2)`
 * @param options special socket options
 */
int ess_socket(ess_socket_fam fam, ess_socket_pro proto, int flags, int options);

/**
 * @brief connect to a dram peer
 *
 *
 * @param socket the socket file desc
 * @param dsthost host of the peer
 * @param dstport port ot the peer
 */
ess_error_t ess_socket_connect_dram(int socket, const std::string& dsthost, const std::string& dstport);
/**
 * @brief disconnect the socket - not available on freeBSD
 * @param socket the socket file desc
 */
ess_error_t ess_socket_disconnect(int socket);
/**
 * @brief Send data to connected socket
 *
 * @param socket the socket file desc
 * @param buf pointer to the data
 * @param len the length of the buffer
 * @param flags flags for `send(2)`
 *
 * @retval n *n* bytes were sent
 * @retval <0 Something went wrong.
 */
unsigned int ess_send(int socket, const void* buf, unsigned int len, int flags);

/**
 * @brief Receive data from a connected DGRAM socket
 *
 * If a datagram socket is connected, this function may be called to receive data sent from
 * the host connected to.
 *
 * @param socket the socket file desc
 * @param buf Area to write the data to
 * @param len how many data we want to receive
 * @param flags Flags to be passed to `recv(2)`
 *
 * @retval >0 n bytes were received.
 * @retval 0 no data were received.
 * @retval -1 Something went wrong.
 */
unsigned int ess_recv(int socket, void* buf, unsigned int len, int flags);

/**
 * @brief send data to connected peer
 * @param socket the socket file desc
 * @param str the to sending string
 */
unsigned int ess_write (int socket, const std::string& str);

/**
 * @brief send data to connected peer (const char)
 * @param socket the socket file desc
 * @param str the to sending string
 * @param len the length of the buffer
 */
unsigned int ess_cwrite (int socket, const char* str, unsigned int lenght);
/**
 * @brief Receive data from connected datagram socket
 *
 * If a datagram socket is connected, you may receive data from it using stream-like functions.
 *
 * @param sock The socket to receive data from
 * @param dest The string to write data to. This string has to be resized to the number of bytes you wish to receive.
 */
unsigned int ess_read(int socket, std::string& str);
/**
 * @brief Receive data from connected datagram socket
 *
 * If a datagram socket is connected, you may receive data from it using stream-like functions.
 *
 * @param sock The socket to receive data from
 * @param dest The buffer  to write data to. This string has to be resized to the number of bytes you wish to receive.
 */
unsigned int ess_cread(int socket, char* str);

#endif
