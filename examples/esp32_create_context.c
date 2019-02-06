#include "ess_context.h"
#include "ess_backend.h"
#include "ess_format.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

ess_context_t *context;
ess_backend_facktory_t* backend_list;
int number_of_backends;

extern "C" void app_main() {
  backend_list =ess_backend_create_factory_list();

  ess_backend_probe_all(ESS_FORMAT_STEREO_96000_24,  &backend_list, &number_of_backends);
  for(int i= 0; i < number_of_backends; i++) {
    printf("Usable backend: %s\n", backend_list[i].get_name());
  }
  context = ess_context_create_ex (&backend_list[0], ESS_FORMAT_STEREO_96000_24);

  ess_backend_destroy_factory_list(backend_list);

  for(;;) { usleep(100000); }
}
