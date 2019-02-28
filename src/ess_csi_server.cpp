#include "ess_csi_server.h"
#include "ess_csi_client.h"
/*
ess_csi_server::ess_csi_server() {
  m_strControllPassword = ESS_CONFIG_CSI_PASSWORD;
}
ess_error_t ess_csi_server::setup(int port) {
  m_pTask = new   ess_csi_server_task(this);

  if(m_pTask == NULL) return ESS_ERROR_NULL;

  if(listen(ESS_DEFAULT_CSI_HOST, port) == ESS_OK) {
    return m_pTask->start();
  }
  return ESS_ERROR;
}
ess_error_t  ess_csi_server::add_client(ess_client_csi* cli) {
  ess_error_t error = ESS_ERROR;

  if(cli->cheak_password("") == ESS_OK) {
    for(int i=0; i < ESS_CONFIG_CSI_MAX_CONNECTIONS; i++) {
      if(m_csiClients[i] == NULL) {
        m_csiClients[i] = cli;
        error = ESS_OK;
      }
    }
  }
  return error;
}
ess_error_t ess_csi_server::send_destroy_to_clients() {
  for(int i=0; i < ESS_CONFIG_CSI_MAX_CONNECTIONS; i++)  {
      if(m_csiClients[i] != NULL) {
        m_csiClients->server_send_stop();
      }
  }
  return ESS_OK;
}
ess_csi_server_task::ess_csi_server_task(ess_csi_server* server)
  : ess_task("ess_csi_server_task", server, 4096) {
    m_bRunServer = true; m_bReady = false;
}
void ess_csi_server_task::onTask(ess_task* self, void* userdata) {
  ess_csi_server *task_user = static_cast<ess_csi_server*>(userdata);
  ess_csi_server_task *task_self =static_cast<ess_csi_server_task*>(self);

  m_bReady = true;
  do {
    ess_client_csi* cl1 = (ess_client_csi*)(task_user->accept());
    if(task_user->add_client(cl1) != ESS_OK) {
      printf("csi is full or wrong password\n");
    } else {
      cl1->start_task(task_user);
    }
  }while(m_bRunServer);

  task_user->send_destroy_to_clients();
}
*/
