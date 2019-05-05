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
 */

#ifndef _ESS_SOCKET_H_
#define _ESS_SOCKET_H_

#include "ess_object.h"
#include "ess_network.h"


/**
 * @brief socket is the base class of every other ess_socket object.
 */
class ess_socket : public ess_object {
public:
  ess_socket(ess_socket_fam fam, ess_socket_type socket_type, ess_socket_proto_t protocolType)
    : ess_socket(fam, socket_type,  protocolType, "ess_socket") { }

  ess_socket(ess_socket_fam fam, ess_socket_type socket_type,
    ess_socket_proto_t protocolType, std::string name);

  virtual ~ess_socket();
  virtual ess_error_t destroy(void);

  ess_socket_fam_t get_family() { return m_eFam; }
  ess_socket_proto_t get_protocol_type() { return m_eProto; }
  ess_socket_type get_socket_type() { return m_fType; }

  bool is_socket() { return m_iSocket != -1; }
  int get_handle(void) const { return m_iSocket;}

protected:
  virtual ess_error_t create();

  int set_opt(int level, ess_socket_option_name_t optname,
    const char* optval, unsigned int optlen) const;

  int get_opt(int level, ess_socket_option_name_t optname,
    char* optval, unsigned int *option_len);

  void set_tcp_nodelay();
protected:
  ess_socket_fam m_eFam;
  ess_socket_type m_fType;
  ess_socket_proto m_eProto;

  int m_iSocket;
};


#endif
