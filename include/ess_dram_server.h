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
 * @file ess_dram_server.h
 * @author Anna Sopdia Schröck
 * @date 19 Februar 2019
 * @brief the OpenESS dram server class
 *
 *
 */
 /**
 * @addtogroup socket
 * @{
 */
#ifndef _ESS_SERVER_H__
#error "#include <ess_server.h> befor this include"
#endif

#ifndef _ESS_SERVER_UDP_H__
#define _ESS_SERVER_UDP_H__

class ess_dram_server : public ess_server {
public:
  ess_dram_server(std::string name, ess_format_t format);

  virtual ess_error_t create(std::string backend_name, std::string host, std::string port) {
    #if ESS_DEFAULT_SERVER_FAMILY == ESS_FAMILY_IP4
      return create(backend_name, host, port, ESS_SOCKET_FAMILY_IP6, false );
    #elif ESS_DEFAULT_SERVER_FAMILY == ESS_FAMILY_IP4
      return create(backend_name, host, port, ESS_SOCKET_FAMILY_IP4, false );
    #else
      return create(backend_name, host, port, ESS_SOCKET_FAMILY_BOTH, false );
    #endif
  }
  virtual ess_error_t create(std::string backend_name, std::string host, std::string port, ess_socket_fam fam) {
    return create(backend_name, host, port, fam, false );
  }
  virtual ess_error_t create(std::string backend_name, std::string host, std::string port, ess_socket_fam fam, bool lite) ;
private:
  ess_inet_dram_server* m_pServerSocket;
};


/**
* @}
*/
#endif
