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
 * @file ess_csi_server.h
 * @author Anna Sopdia Schröck
 * @date 28 Februar 2019
 * @brief OpenESS CSI - Command Socket Interface
 *
 * socket interface - controll from a remote socket
 */
 #ifndef _ESS_SOCKET_SERVER_CSI_H_
 #define _ESS_SOCKET_SERVER_CSI_H_

 /**
 * @addtogroup frontend
 * @{
 */
#include <array>
#include "ess_inet_stream_server.h"
#include "ess_task.h"

class ess_csi_client;
class ess_csi_server;

class ess_csi_server_task : public ess_task {
public:
  ess_csi_server_task(ess_csi_server* server);

  virtual void onTask(ess_task* self, void* userdata);

  bool is_ready() { return m_bReady; }
private:
  bool volatile  m_bReady;
  bool volatile m_bRunServer;
};

#if ESS_CONFIG_CSI_FAMILY == ESS_FAMILY_IP4
class ess_csi_server : public ess_inet_stream_server_ip4 {
#else
class ess_csi_server : public ess_inet_stream_server_ip6 {
#endif
  friend class ess_csi_server_task;
public:
  ess_csi_server();

  ess_error_t setup(int port);
  ess_error_t run();

  ess_csi_client* get_cli(int index);

  std::string get_controll_password() const { return m_strControllPassword; }
  void set_controll_password(std::string password) { m_strControllPassword = password; }

  bool is_task_ready() { return (m_pTask != 0) ?  m_pTask->is_ready() : false; }
public:

  virtual bool cmd_add_client(const std::string& path) { return false; }
protected:
  ess_error_t add_client(ess_csi_client* cli);
  ess_error_t send_destroy_to_clients();
private:
  ess_csi_server_task* m_pTask;
  std::string m_strControllPassword;
  std::array<ess_csi_client*, ESS_CONFIG_CSI_MAX_CONNECTIONS> m_csiClients;
};


 /**
 * @}
 */
 #endif
