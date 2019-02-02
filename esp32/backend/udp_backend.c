#include "config.h"
#ifdef ESS_ENABLE_BACKEND_UDP

#include "backend/udp_backend.h"



int g_udp_paused = 0;

ess_backend_error_t ess_backend_udp_probe(ess_format_t format) {
  switch (format) {
    case ESS_FORMAT_MONO_92000_8:
    case ESS_FORMAT_MONO_92000_16:
    case ESS_FORMAT_MONO_92000_24:
    case ESS_FORMAT_STEREO_92000_8:
    case ESS_FORMAT_STEREO_92000_16:
    case ESS_FORMAT_STEREO_92000_24:
      break;
    default:
      return ESS_BACKEND_OK;
  }
  return ESS_BACKEND_ERROR_WRONG_FORMAT;
}
ess_backend_error_t ess_backend_udp_open(ess_format_t format) {
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_udp_close( void ){
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_udp_pause( void ){
  g_udp_paused = 1;
  return ESS_BACKEND_OK;
}
ess_backend_error_t     ess_backend_udp_write( void *buffer, int buf_size,  int* wrote ){
  if(g_udp_paused) return ESS_BACKEND_PAUSED;
  if(wrote) *wrote = -1;
  return ESS_BACKEND_OK;
}
ess_backend_error_t     ess_backend_udp_read( void *buffer, int buf_size, unsigned int* readed  ){
  if(g_udp_paused) return ESS_BACKEND_PAUSED;
  if(readed) *readed = -1;
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_udp_flush( void ){
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_udp_resume( void ){
  g_udp_paused = 0;
  return ESS_BACKEND_OK;
}
const char* ess_backend_udp_get_name(void) {
  #ifdef ESS_BACKEND_UDP_USING_IP6
  return "udp6-backend";
  #else
  return "udp4-backend";
  #endif
}
const char* ess_backend_udp_get_info(void) {
  return "Network audio backend over udp";
}
ess_backend_facktory_t _udp_backend_config = {
  ess_backend_udp_probe,
  ess_backend_udp_open,
  ess_backend_udp_close,
  ess_backend_udp_pause,
  ess_backend_udp_resume,
  ess_backend_udp_write,
  ess_backend_udp_read,
  ess_backend_udp_flush,
  ess_backend_udp_get_name,
  ess_backend_udp_get_info
};
ess_backend_facktory_t* ess_backend_udp_getFactory() {
  return &_udp_backend_config;
}
#endif
