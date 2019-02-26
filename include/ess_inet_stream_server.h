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
 * @file ess_inet_stream_server.h
 * @author Anna Sopdia Schröck
 * @date 26 Februar 2019
 * @brief Contains the ess_insocket_stream class (TCP internet socket)
 */

#ifndef _ESS_SOCKET_INET_STREAM_SERVER_H_
#define _ESS_SOCKET_INET_STREAM_SERVER_H_

#include "ess_socket.h"
# include <memory>
/**
* @addtogroup socket
* @{
*/
class ess_inet_stream_server : public ess_insocket {
public:
	    ess_inet_stream_server(ess_socket_fam fam);

	    ess_error_t listen(const std::string& bindhost, const int bindport, int flags=0);

	    ess_insocket* accept(int flags=0);
			std::unique_ptr<ess_insocket> accept_ex(int flags=0);

	    const std::string& get_bind_host(void) { return m_strHost;}
	    const int get_bind_port(void) { return m_iPort;}
};


/**
* @}
*/
#endif
