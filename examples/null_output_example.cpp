#include "ess.h"
#include "ess_platform.h"
#include "ess_output_module.h"
#include "ess_input_module.h"

 void app_main() {
  ess_platform::Instance().create();

  ess_output_module* i2s_output = ess_platform::Instance().create_output(ESS_OUTPUT_GENERIC_I2S,
    std::string("ess_i2s_controller") );

  ess_input_module null_input("null_input");
  null_input.add_channel("null_left", ESS_AUDIO_CHANNEL_LEFT);
  null_input.add_channel("null_right", ESS_AUDIO_CHANNEL_RIGHT);

  std::cout << i2s_output << std::endl;

  i2s_output->connect(&null_input, ESS_AUDIO_CHANNEL_LEFT, ESS_AUDIO_CHANNEL_RIGHT);
  i2s_output->connect(&null_input, ESS_AUDIO_CHANNEL_RIGHT, ESS_AUDIO_CHANNEL_LEFT);

  std::cout << i2s_output << std::endl;

  std::cout << "OpenESS is ready to take off" << std::endl;

  for(;;) { i2s_output->update();  }
}

/* Output:

i2s0:0 inputs:
-------------------------
        input: i2s0:0_left(0)
        input: i2s0:0_right(1)
-------------------------
i2s0:0 inputs:
-------------------------
        input: i2s0:0_left(0) <- output: null_right(1)
        input: i2s0:0_right(1) <- output: null_left(0)
-------------------------

OpenESS is ready to take off

*/
