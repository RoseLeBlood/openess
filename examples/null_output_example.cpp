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

  printf("%s\n", i2s_output->to_string().c_str() );

  i2s_output->connect(&null_input, ESS_AUDIO_CHANNEL_LEFT, ESS_AUDIO_CHANNEL_RIGHT);
  i2s_output->connect(&null_input, ESS_AUDIO_CHANNEL_RIGHT, ESS_AUDIO_CHANNEL_LEFT);

  printf("%s\n", i2s_output->to_string().c_str() );

  printf("OpenESS is ready to take off \n");

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
        input: i2s0:0_left(0) <- input: null_right(1)
        input: i2s0:0_right(1) <- input: null_left(0)
-------------------------

OpenESS is ready to take off

*/
