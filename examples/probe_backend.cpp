#include "ess.h"
#include "ess_context.h"

ess_context context;
ess_error_t error;

void probe_backend(ess_backend* backend) {

 printf("Probe backend: %s ----------------------------------------------------\n", backend->get_name() );

 for(int y = 0; y < ESS_FORMAT_MAX; y++)  {
  error = backend->probe(  (ess_format_t) y);

   // ++ => support | !! => no support
    printf("\t\t  %s (%s)   \n", (error == ESS_OK) ? "++" : "!!" ,
      ess_format_to_string( (ess_format_t)(y)) );
   }
}

#if ESS_PLATFORM_ESP32 == 1
extern "C" void app_main() {
#else
int main() {
  ess_backend_t& ins = ess_backend_t::Instance();

  for(auto i = ins.get_backends().begin(); i !=  ins.get_backends().end(); ++i ) {
    probe_backend(i->second);
  }

  for(;;)  { ess_platform_sleep(10); }
}
