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
 * @file ess_insocket_dram.cpp
 * @author Anna Sopdia Schröck
 * @date 18 Februar 20119
 * @brief Contains the inet_dgram class
 */
#include "ess_insocket_dram.h"


# include <iostream>
# include <string>
# include <string.h>
# include <memory>

/**
 * @brief Receives data from peer
 *
 * rcvfrom is the equivalent to `recvfrom(2)`.
 *
 * @param buf Target memory
 * @param len The size of the target memory
 * @retval >0 n bytes of data were read into `buf`.
 * @retval 0 Peer sent EOF
 * @retval -1 Socket is non-blocking and returned without any data.
 */
unsigned int ess_insocket_dram::recvfrom(void* buf, unsigned int len) {
  return ess_vrecvfrom(m_iSocket,buf,len,0);
}
/**
 * @brief rcvfrom for C++ strings, implemented consistently
 *
 * rcvfrom is the equivalent to `recvfrom(2)`.
 *
 * @param buf The string where the received data should be stored at. (auto resize)
 * @retval >0 n bytes of data were read into `buf`.
 * @retval 0 Peer sent EOF
 * @retval -1 Socket is non-blocking and returned without any data.
 */
unsigned int ess_insocket_dram::recvfrom(std::string& buf) {
  return ess_recvfrom(m_iSocket, buf, 0);
}
/**
 * @brief Send data to UDP peer
 *
 * @param buf The data to be sent
 * @param len the size of the to sending memory
 * @param dsthost destination host
 * @param dstport destination port
 *
 * @retval -1 Socket is non-blocking and didn't send any data.
 * @retval >0 n bytes of data were send from `buf` to destination
 * @retval 0 Peer sent EOF
 */
unsigned int ess_insocket_dram::sendto(const void* buf, size_t len, const char* dsthost, const char* dstport) {
  return ess_vsendto(m_iSocket, buf, len, dsthost, dstport);
}
/**
 * @brief Send data to UDP peer
 *
 * @param buf the string to be send
 * @param dsthost destination host
 * @param dstport destination port
 *
 * @retval -1 Socket is non-blocking and didn't send any data.
 * @retval >0 n bytes of data were send from `buf` to destination
 * @retval 0 Peer sent EOF
 */
unsigned int ess_insocket_dram::sendto(const std::string& buf, const std::string& dsthost, const std::string& dstport) {
  return  ess_vsendto(m_iSocket, buf.c_str(), buf.size(), dsthost.c_str(), dstport.c_str());
}
