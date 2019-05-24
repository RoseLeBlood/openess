#include "driver/esp32_driver_task_group.h"
#include "platform/esp32/ess_esp32i2s_output_module.h"
#include "esp_log.h"

esp32_driver_task_group                            _global_driver_group;
ess_esp32i2s_output_module* m_i2s_output;
ess_input_module *null_input;

ess_i2s_controller cmdcon;

void app_main() {
    _global_driver_group.start(1);

    cmdcon.setup();
    m_i2s_output = new ess_esp32i2s_output_module(&cmdcon);
    std::cout << m_i2s_output->to_string() << std::endl;

   null_input = new ess_null_input_module();


   while(!esp32_platform_instance::instance().is_wifi_ready() ) {
      std::cout << "."; ess_platform_sleep(1); }

 // mit udp input tauschen
  m_i2s_output->connect(null_input, ESS_AUDIO_CHANNEL_LEFT, ESS_AUDIO_CHANNEL_LEFT);
  m_i2s_output->connect(null_input, ESS_AUDIO_CHANNEL_RIGHT, ESS_AUDIO_CHANNEL_RIGHT);

  std::cout << m_i2s_output->to_string() << std::endl;

  std::cout << "OpenESS v. " << LIBOPEN_ESS_VERSION_STRING  << "  started" << std::endl;


  for(;;) {  m_i2s_output->update(); }
}
