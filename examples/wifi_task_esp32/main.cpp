
#include "wifi_task.h"

wifi_task wifi("OpenESS Daemon", "Qwertz1234" );


extern "C" void app_main() {
  ess_error_t error = wifi.start();
  ESS_ERROR(error) ; while(!wifi.is_ready()) { sleep(5); }

  printf("Wifi is ready to take off \n");

  for(;;)  { ess_platform_sleep(10); }
}
