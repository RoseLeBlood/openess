#include "ess.h"
#include "ess_server.h"
#include "ess_dram_server.h"

#include "wifi_task.h"

wifi_task task("OpenESS-DRAm_Server", "Qwertz1234");
ess_dram_server server("OpenESS_Server", ESS_FORMAT_STEREO_44100_16);

extern "C" void app_main() {
  ess_error_t error = task.start();
  ESS_ERROR(error) ; while(!task.is_ready()) { sleep(5); }

  printf("Wifi is ready to take off \n");

  error = server.create(ESS_BACKEND_NAME_I2S_ESP32,
    ESS_DEFAULT_SERVER_HOST,
    ESS_DEFAULT_SERVER_PORT);
  ESS_ERROR(error) ;

  printf("dram server created on: %s:%s\n", ESS_DEFAULT_SERVER_HOST, ESS_DEFAULT_SERVER_PORT );
  for(;;)  { ess_platform_sleep(10); }
}
