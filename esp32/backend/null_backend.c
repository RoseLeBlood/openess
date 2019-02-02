#include "backend/null_backend.h"


int g_null_paused = 0;

ess_backend_error_t ess_backend_null_probe(ess_format_t format) {
  return ESS_BACKEND_OK;
}
ess_backend_error_t ess_backend_null_open(ess_format_t format) {
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_null_close( void ){
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_null_pause( void ){
  g_null_paused = 1;
  return ESS_BACKEND_OK;
}
ess_backend_error_t     ess_backend_null_write( void *buffer, int buf_size,  int* wrote ){
  if(g_null_paused) return ESS_BACKEND_PAUSED;
  if(wrote) *wrote = -1;
  return ESS_BACKEND_OK;
}
ess_backend_error_t     ess_backend_null_read( void *buffer, int buf_size, unsigned int* readed  ){
  if(g_null_paused) return ESS_BACKEND_PAUSED;
  if(readed) *readed = -1;
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_null_flush( void ){
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_null_resume( void ){
  g_null_paused = 0;
  return ESS_BACKEND_OK;
}
const char* ess_backend_null_get_name(void) {
  return "null";
}
const char* ess_backend_null_get_info(void) {
  return "Null Audio";
}
ess_backend_facktory_t _null_backend_config = {
  ess_backend_null_probe,
  ess_backend_null_open,
  ess_backend_null_close,
  ess_backend_null_pause,
  ess_backend_null_resume,
  ess_backend_null_write,
  ess_backend_null_read,
  ess_backend_null_flush,
  ess_backend_null_get_name,
  ess_backend_null_get_info
};
ess_backend_facktory_t* ess_backend_null_getFactory() {
  return &_null_backend_config;
}
