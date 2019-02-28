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
 * @file ess_csi_client.h
 * @author Anna Sopdia Schröck
 * @date 28 Februar 2019
 * @brief OpenESS CSI - Command Socket Interface client
 *
 * socket interface - controll from a remote socket (client)
 */
 #ifndef _ESS_SOCKET_SERVER_CSI_H_
 #define _ESS_SOCKET_SERVER_CSI_H_

#include "ess_task.h"

 /**
 * @addtogroup frontend
 * @{
 */

class ess_csi_client : public ess_insocket {
public:

  ess_error_t cheak_password(std::string password) { return ESS_OK; }
  ess_error_t start_task(ess_csi_server* server) { m_pServer = server; return ESS_OK; }

  ess_error_t server_send_stop() { return ESS_OK; } 
private:
  ess_csi_server* m_pServer;
  ess_csi_client_task* m_pTask;
};

  /**
  * @}
  */
  #endif
