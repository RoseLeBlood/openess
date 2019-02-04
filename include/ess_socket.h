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
 * @file format.h
 * @author Anna Sopdia Schröck
 * @date 2 Februar 20119
 * @brief Contains all ess socket functions.
 * It contains all functions used to work with INET and INET6 sockets, both TCP, UDP, UDP lite
 *
 * 
 */

#ifndef _ESS_SOCKET_H_
#define _ESS_SOCKET_H_

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
 * @brief ess_socket error
 */
typedef enum ess_socket_error {
  ESS_SOCKET_ERROR_OK = 0,                                 /**< no error*/
  ESS_SOCKET_ERROR_NULL = -1,                           /**< `ess_socket_t` is NULL */
  ESS_SOCKET_ERROR_UNSPEC_PROTOKOL,      /**< unknown protokol */
  ESS_SOCKET_ERROR_UNSPEC_FAMILY,              /**< unknown family */
  ESS_SOCKET_ERROR_UNSPEC,
  ESS_SOCKET_ERROR_GETADDR,                            /**<  getaddrinfo error see  ess_socket_t::retval */
  ESS_SOCKET_ERROR_BIND,                                     /**<  bind error see  ess_socket_t::retval  */
  ESS_SOCKET_ERROR_CLOSE,                                     /**<  close error see  ess_socket_t::retval  */
}ess_socket_error_t;

/**
 * @brief hold all socket managment importend data
 */
typedef struct ess_socket {
  char hostname[32];                     /**<  Address to bind. If you want to bind to every address use "0.0.0.0" or "::" (IPv6 wildcard) */
  unsigned short port;                    /**<  The port to bind. */
  int socket;                                   /**<  The socket */
  int retval;
  ess_socket_pro_t protokol;          /**< `ESS_SOCKET_PROTO_STREAM`, `ESS_SOCKET_PROTO_DRAM` or `ESS_SOCKET_PROTO_DRAM_LITE` - the using protokoll */
  ess_socket_fam_t family;            /**<  `ESS_SOCKET_FAMILY_IP4`, `ESS_SOCKET_FAMILY_IP6` or `ESS_SOCKET_FAMILY_BOTH`; latter means that the DNS resolver should decide. */
  ess_socket_status_t status;          /**< ess_socket status */
}ess_socket_t;

/**
 * @brief Look up which address families a host supports.
 *
 * If you want to send a datagram to a host but you don't know
 * if it supports IPv4 or IPv6, use this function.
 *
 * @param hostname The hostname of the host you want to look up.
 *
 * @retval ESS_SOCKET_FAMILY_IP4 Host supports only IP4
 * @retval ESS_SOCKET_FAMILY_IP6 Host supports IP6 and IP4
 * @retval <0 Error.
 */
ess_socket_fam_t ess_get_address_family(const char* hostname);

/**
* @brief setup the ess_socket structure
*
* @param socket the ess_socket_t structure to fill

* @param protokoll  `ESS_SOCKET_PROTO_STREAM`, `ESS_SOCKET_PROTO_DRAM` or `ESS_SOCKET_PROTO_DRAM_LITE`
* @param fam Either `ESS_SOCKET_FAMILY_IP4`, `ESS_SOCKET_FAMILY_IP6` or `ESS_SOCKET_FAMILY_BOTH`; latter means that the DNS resolver should decide.
* @param bind_addr Address to bind to. If you want to bind to every address use "0.0.0.0" or "::" (IPv6 wildcard)
* @param port The port to bind to.
*
* @retval ESS_SOCKET_ERROR_OK
*/
ess_socket_error_t ess_socket_create(ess_socket_t* socket, ess_socket_fam_t fam, ess_socket_pro_t protokoll,
                                                             const char* addr, unsigned short port);


/**
* @brief Create a TCP or UDP server socket
* @param socket the using socket struct
* @retval ESS_SOCKET_ERROR_OK the socket was created  - TCP socket are listin
* @retval ESS_SOCKET_ERROR_UNSPEC socket alwas created
* @retval ESS_SOCKET_ERROR_UNSPEC_PROTOKOL unknown protokol
* @retcal ESS_SOCKET_ERROR_UNSPEC_FAMILY unknown family
* @retval ESS_SOCKET_ERROR_GETADDR
* @retval ESS_SOCKET_ERROR_BIND error to call bind
* @retval ESS_SOCKET_ERROR_NULL socket was NULL
*/
ess_socket_error_t ess_socket_create_server(ess_socket_t* socket);

/**
 * @brief Close a socket.
 *
 * This function closes a socket.
 *
* @param socket the using socket struct
 *
 * @retval ESS_SOCKET_ERROR_OK Closed socket successfully
 * @retval ESS_SOCKET_ERROR_NULL socket was NULL
 * @retval ESS_SOCKET_ERROR_CLOSE Socket was already closed (other errors are very unlikely to occur)
 */
ess_socket_error_t ess_socket_close(ess_socket_t* socket);


#endif
