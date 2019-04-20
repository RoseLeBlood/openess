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

  std::cout << std::endl << "Wifi is ready to take off" << std::endl;

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

/*
Output:
....
Wifi is ready to take off
[MEM] Init on 1073494632 with 16
I (5157) I2S: DMA Malloc info, datalen=blocksize=2048, dma_buf_count=3
I (5157) I2S: DMA Malloc info, datalen=blocksize=2048, dma_buf_count=3
I (5167) I2S: APLL: Req RATE: 44100, real rate: 43945.238, BITS: 16, CLKM: 1, BCK_M: 8, MCLK: 11249981.000, SCLK: 1406247.625000, diva: 1, divb: 0
I (5177) I2S: APLL: Req RATE: 44100, real rate: 43945.238, BITS: 16, CLKM: 1, BCK_M: 8, MCLK: 11249981.000, SCLK: 1406247.625000, diva: 1, divb: 0
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
5060 ms uptime
CPU0: 7.94446e-33 %[ 2.35142e-38 % ]
CPU1: -0.0339525 %[ 1.34525e-43 % ]
i2s0:0 ld:  98487.6 cl: 686063449 cla: 218847 ldsec: 401.369 clsec: 963286438

mem: 0 / 2
6070 ms uptime
CPU0: 7.94446e-33 %[ 2.35142e-38 % ]
CPU1: -0.0339525 %[ 1.34525e-43 % ]
i2s0:0 ld:  98487.6 cl: 686063449 cla: 218847 ldsec: 401.369 clsec: 963286438

mem: 0 / 2
7070 ms uptime
CPU0: 0.0914584 %[ 0.0914584 % ]
CPU1: -0.0339525 %[ 1.34525e-43 % ]
i2s0:0 ld:  98487.6 cl: 686063449 cla: 218847 ldsec: 401.369 clsec: 963286438

mem: 0 / 2

--- exit ---*/
