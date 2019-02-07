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

#include "ess_error.h"

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
 * @brief hold all socket managment importend data
 */
typedef struct ess_socket {
  char hostname[64];                     /**<  Address to bind or client hostname. If you want to bind to every address use "0.0.0.0" or "::" (IPv6 wildcard) */
  unsigned int hostname_len;            /** < hostname length*/
  unsigned int port;                    /**<  The port to bind. */

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
* @brief Create a TCP or UDP server socket
*
* @param protokoll  `ESS_SOCKET_PROTO_STREAM`, `ESS_SOCKET_PROTO_DRAM` or `ESS_SOCKET_PROTO_DRAM_LITE`
* @param fam Either `ESS_SOCKET_FAMILY_IP4`, `ESS_SOCKET_FAMILY_IP6` or `ESS_SOCKET_FAMILY_BOTH`; latter means that the DNS resolver should decide.
* @param bind_addr Address to bind to. If you want to bind to every address use "0.0.0.0" or "::" (IPv6 wildcard)
* @param port The port to bind to.
* @param socket the using socket struct
*
* @retval ESS_OK the socket was created  - TCP socket are listin
* @retval ESS_ERROR_UNSPEC socket alwas created
* @retval ESS_ERROR_UNSPEC_PROTOKOL unknown protokol
* @retcal ESS_ERROR_UNSPEC_FAMILY unknown family
* @retval ESS_ERROR_GETADDR
* @retval ESS_ERROR_BIND error to call bind
* @retval ESS_ERROR_NULL socket was NULL
*/
ess_error_t ess_socket_create_server( ess_socket_fam_t fam, ess_socket_pro_t protokoll,
                                                             const char* addr, unsigned short port, ess_socket_t* socket);
/**
 * @brief accept a connection attempt on a server socket.
 *
 * This function accepts an incoming connection on a server socket.
 *
 * @param server_socket the server socket
 * @param error_code
 *
 * @retval != 0 A the client socket
 * @retval NULL Error  see paramerter 'error_code'
 */
ess_socket_t* ess_socket_accept(ess_socket_t* server_socket, ess_error_t* error_code);



/**
 * @brief Close a socket.
 *
 * This function closes a socket.
 *
* @param socket the using socket struct
 *
 * @retval ESS_OK Closed socket successfully
 * @retval ESS_ERROR_NULL socket was NULL
 * @retval ESS_ERROR_CLOSE Socket was already closed (other errors are very unlikely to occur)
 */
ess_error_t ess_socket_close(ess_socket_t* socket);

/**
 * @brief perform a `shutdown(2)` call on a socket  (write)
 *
 * This function closes a socket.
 *
 * @param socket the using socket struct
 *
 * @retval ESS_OK Closed socket successfully
 * @retval ESS_ERROR_NULL socket was NULL
 * @retval ESS_ERROR_CLOSE Socket was already closed (other errors are very unlikely to occur)
 */
ess_error_t ess_socket_end_write(ess_socket_t* socket);
/**
 * @brief perform a `shutdown(2)` call on a socket  (read)
 *
 * @param socket the using socket struct
 *
 * @retval ESS_OK Closed socket successfully
 * @retval ESS_ERROR_NULL socket was NULL
 * @retval ESS_ERROR_CLOSE Socket was already closed (other errors are very unlikely to occur)
 */
ess_error_t ess_socket_end_read(ess_socket_t* socket);
/**
 * @brief perform a `shutdown(2)` call on a socket  (read/write)
 *
 * @param socket the using socket struct
 *
 * @retval ESS_OK Closed socket successfully
 * @retval ESS_ERROR_NULL socket was NULL
 * @retval ESS_ERROR_CLOSE Socket was already closed (other errors are very unlikely to occur)
 */
ess_error_t ess_socket_end(ess_socket_t* socket);

/**
 * @brief set send and recive buffer size of the socket
 *
 * @param socket the using socket struct
 * @param rec_buffer_size the size of the raed buffer
 * @param send_buffer_size the size of the send buffer
 * @retval ESS_OK Closed socket successfully
 * @retval ESS_ERROR_NULL socket was NULL
 * @retval ESS_ERROR_CLOSE Socket was already closed (other errors are very unlikely to occur)
 */
ess_error_t ess_socket_set_buffer(ess_socket_t* socket, unsigned int rec_buffer_size,
   unsigned int send_buffer_size);

   /**
    * @brief Create and connect a new TCP/IP socket
    *
    * This function returns a working client TCP/IP socket.
    *
    * @param hostname The host the socket will be connected to (everything resolvable, e.g. "::1", "8.8.8.8", "example.com")
    * @param port The host's port.
    * @param family `ESS_SOCKET_FAMILY_IP6` or `ESS_SOCKET_FAMILY_IP4`.
    * @param flags Flags to be passed to `socket(2)`. Most flags are Linux-only!
    * @param error_code ESS_ERROR_NULL hostname was NULL
    *
    *
    * @retval NULL Error  see paramerter 'error_code'
    * @return A valid socket.
    */
ess_socket_t* ess_socket_connect_stream(const char* hostname, int port, ess_socket_fam_t family, int flags, ess_error_t* error_code) ;


/**
 * @brief Creates a new UDP/IP socket
 *
 *  The socket is automatically bound to some port.
 *
 * @param [in] fam is ESS_SOCKET_FAMILY_IP4  (AF_INET) or ESS_SOCKET_FAMILY_IP6  (AF_INET6).
 * @param [in] proto is ESS_SOCKET_PROTO_DRAM or ESS_SOCKET_PROTO_DRAM_LITE
 * @param [in]  flags may be the flags specified in socket(2), i.e. SOCK_NONBLOCK and/or SOCK_CLOEXEC. More than one
 * flags may be ORed. This argument is only sensible on Linux >= 2.6.27!
 * @param [out] error_code if !=0 then error codes
 *
 * @return The socket file descriptor number, on error NULL.
 *
 * To send and receive data with this socket use the functions explained below, ess_socket_read_dram() and ess_socket_write_dram().
 */
ess_socket_t* ess_socket_create_dram(ess_socket_fam_t  fam, ess_socket_pro_t proto, int flags, ess_error_t* error_code);
/**
 * @brief connect a new UDP socket
 *
 * This function returns a working client UDP socket.
 *
 * @param hostname The host the socket will be connected to (everything resolvable, e.g. "::1", "8.8.8.8", "example.com")
 * @param port The host's port.
 * @param family `ESS_SOCKET_FAMILY_IP6` or `ESS_SOCKET_FAMILY_IP4`.
 * @param prot `ESS_SOCKET_PROTO_DRAM` or `ESS_SOCKET_PROTO_DRAM_LITE`
 * @param error_code ESS_ERROR_NULL hostname was NULL
 *
 *
 * @retval NULL Error  see paramerter 'error_code'
 * @return A valid socket.
 */
ess_error_t ess_socket_connect_dram(ess_socket_t* socket, const char* hostname, int port) ;


/**
 * @brief This function is the equivalent to `sendto(2)`
 *
 * @param [in] the socket you got from `ess_socket_create_dram`.
 * @param buf is a pointer to some data.
 * @param size is the length of the buffer .
 * @param host is the host to which we want to send the data.
 * @param port is the port on the remote host.
 * @param sendto_flags is available on all platforms. The value given here goes directly to the internal sendto() call.
 * @param [out] error Error codes
 *
 * @retval n *n* bytes of data could be sent.
 * @retval ESS_ERROR_UNSPEC Unsopec error.
 * @retval ESS_ERROR_NULL size, host or socket is NULL
 */
ess_error_t ess_socket_write_dram(ess_socket_t* socket, const void* buf, unsigned int size,
  const char* host, int port, int sendto_flags);

/**
 * @brief Receive data from a UDP/IP socket
 *
 *
 * @param [in] the socket you got from `ess_socket_create_dram`.
 * @param buf where the data will be written
 * @param size the size of `buffer`
 * @param src_host Where the sending host's name/IP will be stored
 * @param src_host_len `src_host`'s length
 * @param src_port where the port on remote side will be written to
 * @param recvfrom_flags Flags for `recvfrom(2)`
 *
 * @retval n *n* bytes of data were received.
 * @retval 0 Peer sent EOF.
 * @retval <0 An error occurred.
 */
ess_error_t ess_socket_read_dram(ess_socket_t* socket, void* buf, unsigned int size, char* src_host,
  unsigned int src_host_len, int  src_port, int recvfrom_flags);


/**
* @brief read from socket
*
*
* @param [in] the remote socket
* @param buffer where the data will be read
* @param size the size of `buffer`
* @param readed how many bytes readed
*
*
* @retval ESS_OK all ok
* @retval ESS_SOCKET_UNSPEC Error
*/
ess_error_t ess_socket_read(ess_socket_t* socket, void* buffer, unsigned int size, unsigned int* readed);
/**
* @brief read from socket
*
*
* @param [in] the remote socket
* @param buffer where the data will be read
* @param size the size of `buffer`
* @param wrote how many bytes wrote
*
*
* @retval ESS_OK all ok
* @retval ESS_SOCKET_UNSPEC Error
*/
ess_error_t ess_socket_write(ess_socket_t* socket, const void* buffer, unsigned int size, unsigned int* wrote);

#endif
