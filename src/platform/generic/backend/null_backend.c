#include "ess_format.h"
#include "config.h"
#include "ess_backend.h"
#include "stdio.h"

int g_null_paused = 0;

ess_backend_error_t ess_backend_null_probe(const ess_format_t format) {
  printf("Possible to probe backend: null (%s)\n",
  ess_format_to_string(format));
  return ESS_BACKEND_OK;
}
ess_backend_error_t ess_backend_null_open(const ess_format_t format) {
  printf("Possible to open backend: null (%s)\n",
  ess_format_to_string(format));
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_null_close( void ){
  printf("Possible to close backend: null\n");
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_null_pause( void ){
  printf("Possible to pause backend: null\n");
  return ESS_BACKEND_OK;
}
ess_backend_error_t     ess_backend_null_write( void *buffer, unsigned int buf_size,  unsigned int* wrote ){
  if(wrote) *wrote = -1;
  return ESS_BACKEND_OK;
}
ess_backend_error_t     ess_backend_null_read( void *buffer, unsigned int buf_size, unsigned int* readed  ){
  if(readed) *readed = -1;
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_null_flush( void ){
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_null_resume( void ){
  printf("Possible to resume backend: null\n");
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_null_set_sample_format(const ess_format_t format) {
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
  ess_backend_null_set_sample_format,
  ess_backend_null_get_name,
  ess_backend_null_get_info,
  0
};
ess_backend_facktory_t* ess_backend_null_getFactory() {
  return &_null_backend_config;
}
