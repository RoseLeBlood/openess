#include "ess_context.h"
#include "ess_format.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


extern "C" void app_main() {
  ess_context_t context;
  ess_context_error_t error;

  error = ess_context_create (&context, ESS_BACKEND_NAME_I2S_ESP32, ESS_FORMAT_STEREO_44100_16);
  if(error != ESS_CONTEXT_ERROR_OK) printf("error in creating the context\n");

  for(;;) { usleep(100000); }
}
