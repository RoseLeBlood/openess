#ifndef _ESS_SERVER_H__
#define _ESS_SERVER_H__

#include "esd.h"
#include "context.h"
#include "ess_socket.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum ess_server_status {
  ESS_SERVER_STATUS_STOP,
  ESS_SERVER_STATUS_RUN,
  ESS_SERVER_STATUS_STANDBY,
  ESS_SERVER_STATUS_ERROR
}ess_server_status_t;

typedef struct ess_server {
  ess_socket_t socket;
  ess_backend_t* backend;
  ess_format_t format;

  void* buffer;
  int magl, magr;
  int  speed,  length, offset ;

  ess_server_status_t status;
} ess_server_t;

int ess_server_start(ess_server_t* server, const char* backend_name) ;
int ess_server_stop(ess_server_t* server);
int ess_restart_server(ess_server_t* server);

int ess_standby_server(ess_server_t* server);
int ess_resume_server(ess_server_t* server);

int ess_open_listen_socket(ess_server_t* server) ;

void ess_set_audio_buffer(ess_server_t* server);

#ifdef __cplusplus
}
#endif

#endif
