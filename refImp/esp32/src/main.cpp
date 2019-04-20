#include "ess.h"
#include "ess_platform.h"
#include "ess_output_module.h"
#include "ess_input_module.h"
#include "ess_null_input_module.h"
#include "ess_debug.h"

#include "wifi_task.h"

wifi_task task(ESS_DEFAULT_SERVER_NAME, "Qwertz1234");

void app_main() {
  ess_error_t error = task.start();
  ESS_ERROR(error) ; while(!task.is_ready()) { printf("."); sleep(1); }

  std::cout << "Wifi is ready to take off" << std::endl;

  ess_platform::Instance().create();

  ess_output_module* i2s_output = ess_platform::Instance().create_output(ESS_OUTPUT_I2S,
    ESS_I2S_STD_CONTROLLER );

  std::cout << i2s_output->to_string() << std::endl;

  ess_input_module *null_input = new ess_null_input_module();
  i2s_output->connect(null_input, ESS_AUDIO_CHANNEL_LEFT, ESS_AUDIO_CHANNEL_RIGHT);
  i2s_output->connect(null_input, ESS_AUDIO_CHANNEL_RIGHT, ESS_AUDIO_CHANNEL_LEFT);

  std::cout << i2s_output->to_string() << std::endl;

  for(;;) { ess_debug( (ess_output_analyzed_module*)  i2s_output);   }
}
