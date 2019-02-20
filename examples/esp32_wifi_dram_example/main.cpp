#include "ess.h"
#include "ess_server.h"
#include "ess_dram_server.h"

#include "wifi_task.h"

wifi_task task(ESS_DEFAULT_SERVER_NAME, "Qwertz1234");
ess_dram_server server(ESS_DEFAULT_SERVER_NAME, ESS_FORMAT_STEREO_44100_16);

extern "C" void app_main() {
  ess_error_t error = task.start();
  ESS_ERROR(error) ; while(!task.is_ready()) { printf("."); sleep(1); }

  printf("Wifi is ready to take off \n");

  error = server.create(ESS_BACKEND_NAME_I2S_ESP32);
  ESS_ERROR(error) ;

  for(;;)  { ess_platform_sleep(10); }
}
