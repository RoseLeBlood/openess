#include "context.h"
#include "backend.h"

#include "WiFi.h"
#include "mdns.h"
#include "format.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <math.h>
#include <errno.h>
#include <sys/select.h>

void start_mdns_service(char* format,  char* backend) {
  mdns_init();
  mdns_hostname_set("ess");
  mdns_instance_name_set("Embedded SoundSystem on ESP32");

  mdns_txt_item_t serviceTxtData[3] = {
    {"board", "esp32"},
    {"format", format },
    {"backend", backend},
  };
  printf("Add mdns service ess  (format: %s on %s)\n", format, backend);
  mdns_service_add(NULL, "_sound", "_tcp", ESD_DEFAULT_PORT, serviceTxtData, 3);
}


WiFi g_appWifi;

ess_context_t context;
ess_backend_facktory_t* backend_list;

extern "C" void app_main() {
  backend_list = (ess_backend_facktory_t*)malloc(sizeof(ess_backend_facktory_t) * ess_backend_get_size());

  ess_backend_probe_all(ESS_FORMAT_STEREO_96000_24,  &backend_list);
  ess_context_create(&context, ESS_FORMAT_STEREO_96000_24);
  ess_context_init_ex(&context, &backend_list[1]);

  char format[16], backend[16];
  sprintf(format,"%s", ess_format_to_string(context.format));
  sprintf(backend,"%s",  ess_context_get_backend_name(&context));

  start_mdns_service(format, backend);

  g_appWifi.startAP("ESP32-EsoundD", "fhj");

  for(;;) { usleep(100000); }
}
