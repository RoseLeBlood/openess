**OpenESS 0.6.04**   is a network-capable sound server libary mainly for embedded systems and other operatins systems.
OpenESS is free and open-source software, and is licensed under the terms of the GNU Lesser General Public License.

<a href="https://www.codacy.com/app/RoseLeBlood/openess?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=RoseLeBlood/openess&amp;utm_campaign=Badge_Grade"><img src="https://api.codacy.com/project/badge/Grade/4f0ba2c68a904b8da2f1d45d5f3596d4"/></a>
<img src="https://img.shields.io/github/license/RoseLeBlood/Openess.svg"/>
<img src="https://img.shields.io/github/last-commit/roseleblood/openess.svg"/>
<a href="https://twitter.com/padersophia">
<img src="https://img.shields.io/twitter/follow/padersophia.svg"></a>


## Getting Started

### Setting Up Development Environment

#### PlatformIO

OpenESS++ is made for use with [platformio](http://platformio.org/), an advanced ecosystem for microcontroller
development. To get started with coding esphomelib applications, you first have to
[install the atom-based platformio IDE](http://platformio.org/platformio-ide) or for advanced users,
[install the command line version of platformio](http://docs.platformio.org/en/latest/installation.html).

Then create a new project for an [ESP32-based board](http://docs.platformio.org/en/latest/platforms/espressif32.html#boards)
(for example, `nodemcu-32s`). Then open up the newly created `platformio.ini` file and insert

```ini
; ...
platform = espressif32
board = nodemcu-32s
framework = esp-idf
lib_deps = openess
```
Finally, create a new source file in the `src/` folder (for example `main.c`) and start coding with openess.

## Usage example

_simple create output_
```cpp
#include "ess.h"
#include "ess_platform.h"
#include "ess_output_module.h"
#include "ess_input_module.h"

 void app_main() {
   ess_platform::Instance().create();

   ess_output_module* i2s_output = ess_platform::Instance().create_output(ESS_OUTPUT_GENERIC_I2S,
     std::string("ess_i2s_controller") );

   std::cout << i2s_output->to_string() << std::endl;


   printf("OpenESS is ready to take off \n");

   for(;;) { i2s_output->update();  }
}

/* Output:

I (5153) I2S: DMA Malloc info, datalen=blocksize=512, dma_buf_count=3
I (5153) I2S: DMA Malloc info, datalen=blocksize=512, dma_buf_count=3
I (5153) I2S: APLL: Req RATE: 48000, real rate: 47999.961, BITS: 16, CLKM: 1, BCK_M: 8, MCLK: 12287990.000, SCLK: 1535998.750000, diva: 1, divb: 0
I (5173) I2S: APLL: Req RATE: 48000, real rate: 47999.961, BITS: 16, CLKM: 1, BCK_M: 8, MCLK: 12287990.000, SCLK: 1535998.750000, diva: 1, divb: 0
i2s0:0 inputs:
-------------------------
        input: i2s0:0_left(0)
        input: i2s0:0_right(1)
-------------------------

OpenESS is ready to take off

*/
```

_null output example_
```cpp
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

  std::cout << i2s_output->to_string() << std::endl;


  i2s_output->connect(&null_input, ESS_AUDIO_CHANNEL_LEFT, ESS_AUDIO_CHANNEL_RIGHT);
  i2s_output->connect(&null_input, ESS_AUDIO_CHANNEL_RIGHT, ESS_AUDIO_CHANNEL_LEFT);

  std::cout << i2s_output->to_string() << std::endl;

  std::cout << "OpenESS is ready to take off" << std::endl;

  for(;;) { i2s_output->update();  }
}
/* Output:

I (5153) I2S: DMA Malloc info, datalen=blocksize=512, dma_buf_count=3
I (5153) I2S: DMA Malloc info, datalen=blocksize=512, dma_buf_count=3
I (5153) I2S: APLL: Req RATE: 48000, real rate: 47999.961, BITS: 16, CLKM: 1, BCK_M: 8, MCLK: 12287990.000, SCLK: 1535998.750000, diva: 1, divb: 0
I (5173) I2S: APLL: Req RATE: 48000, real rate: 47999.961, BITS: 16, CLKM: 1, BCK_M: 8, MCLK: 12287990.000, SCLK: 1535998.750000, diva: 1, divb: 0
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
```
_For more examples and usage, please refer to the [Wiki][wiki]

## Current Features

* Powerful core that allows for easy to port
* Powerful socket abscrations layer (SAL) only dram and dramlite at the moment
* Easy to use platform configuration
* mutex, spinlock, task and ringbuffer handling on various platform (current only esp32)
* generic backends:  i2s, more work in progress
* task are multitaskin safe
* code style min B
* C++ System

## Progressed features (when ready than version 0.9)

* running example server on esp32 and linux
* audio mixing from multiple clients
* MQTT status upport and logging
* mDNS
* code style

## Planned features

* Improve documentation

* **Suggestions?** Feel free to create an issue and tag it with feature request.


## Release History
* 0.6.04:
  - remove TeensyAudioLibrary
  - add very flexible audio system
  - rename class see examples
  - add ess_channel
  - add connecting system
  - fix issus
* 0.5.0:
  - update to 0.5
  - start impl new frontend system. based on the TeensyAudioLibrary with modifications
  - rename backends:
      - i2s_generic_backend -> i2s_generic_output_backend
      - generic_openal_backend -> generic_openal_output_backend
      - generic_udp_backend -> generic_udp_output_backend
* 0.4.5:
  - add IP4/IP6 multicast
  - add new system
  - remove ess_context
* 0.4.2:
  - remove issus
* 0.4.03
  - ++ ess_backend::get_blksize
  - ++ config ESS_BUF_COUNT 4
  - ++ config ESS_BUF_SIZE      1024
* 0.4.02
  - add ess_network.h for socket multiplatform layer
  - update example
  - ess_dram_server using config from config.h
  - add generic_udp_backend
* 0.4.0
  - add udp_inet server / client backend
  - add ess_server and ess_dram_server (basic)
  - add esp32 dram server example
* 0.3.4
  - add backend factory
  - add context creating functions
  - add probe function to ess_backend as virtual
  - add esp32 i2s_generic_backend
* 0.3.3
  - rename project to OpenESS ++
  - switch to C++
  - C++ convert i progress - unstable
* 0.3
  - update platform abstraction layer
  - add mutex, task and spinlock functions - task using mutex on esp32 platforms
  - add examples
* 0.2
  - rename headers
  - add platform abstraction layer
* 0.0.1
  - Work in progress


[wiki]: https://github.com/RoseLeBlood/openess/wiki
