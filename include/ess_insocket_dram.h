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
 * @file ess_insocket_dram.h
 * @author Anna Sopdia Schröck
 * @date 18 Februar 20119
 * @brief Contains ess_socket (base class) and ess_insocket (base for all internet sockets)
 */

#ifndef _ESS_SOCKET_INET_DGRAM_H_
#define _ESS_SOCKET_INET_DGRAM_H_

#include "ess_socket.h"

/**
* @addtogroup ess_socket (SAL)
* @{
*/
class ess_insocket_dram : public ess_insocket {
public:
  ess_insocket_dram() : ess_insocket(ESS_SOCKET_FAMILY_IP4, ESS_SOCKET_PROTO_DRAM) { }
  ess_insocket_dram(ess_socket_fam fam) : ess_insocket(fam, ESS_SOCKET_PROTO_DRAM) { }

  virtual unsigned int write(const void* buf, unsigned int len, const char* dsthost, const char* dstport); //
  virtual unsigned int write(const std::string& buf, const std::string& dsthost, const std::string& dstport); //

  virtual unsigned int read(void* buf, unsigned int len); //
  virtual unsigned int read(std::string& buf); //

protected:
  ess_insocket_dram(ess_socket_fam fam, ess_socket_pro proto) : ess_insocket(fam, proto) { }
};
/**
* @}
*/
#endif
