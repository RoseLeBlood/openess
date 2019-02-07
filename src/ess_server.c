#include "ess_server.h"

ess_error_t ess_server_start(ess_server_t* server, ess_context_t* context,  ess_format_t format)  {
  if(server == 0 || context == 0) return ESS_ERROR_NULL;

  ess_socket_pro_t proto;
  ess_socket_fam_t fam;

  #if ESS_DEFAULT_SERVER_PROTOCOL == ESS_PROTOCOL_TCP
    proto = ESS_SOCKET_PROTO_STREAM;
  #elif ESS_DEFAULT_SERVER_PROTOCOL == ESS_PROTOCOL_UDP
    proto = ESS_SOCKET_PROTO_DRAM;
  #else
    proto = ESS_SOCKET_PROTO_DRAM_LITE;
  #endif

  #if ESS_DEFAULT_SERVER_FAMILY == ESS_FAMILY_IP6
    fam = ESS_SOCKET_FAMILY_IP6;
  #elif ESS_DEFAULT_SERVER_FAMILY == ESS_FAMILY_IP4
    fam = ESS_SOCKET_FAMILY_IP4;
  #else
    fam = ESS_SOCKET_FAMILY_BOTH  ;
  #endif

  ess_error_t error = ess_socket_create_server(fam, proto, ESS_DEFAULT_SERVER_HOST,
      ESS_DEFAULT_SERVER_PORT, &server->socket);

  server->format = format;
  server->context = context;
  server->status = ESS_SERVER_STATUS_RUN;
  
  return error;
}
