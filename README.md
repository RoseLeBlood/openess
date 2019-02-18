
<div>
 <img src="https://roseleblood.github.io/openess/Logo-OpenESS.png" width="256" align="left">
 <div align="left">
  <h1>Open Embedded Sound Server ++</h1>
   <h3>
     <a href="https://roseleblood.github.io/">Website</a>
     <span> | </span>
     <a href="https://github.com/RoseLeBlood/openess/wiki">
       Wiki
     </a>
     <span> | </span>
     <a href="https://github.com/RoseLeBlood/openess/blob/master/CONTRIBUTING.md">
       Contributing
     </a>
     <span> | </span>
     <a href="https://roseleblood.github.io/openess/html/d3/dcc/md__r_e_a_d_m_e.html">
       Documentation
     </a>
     <span> | </span>
     <a href="https://webchat.freenode.net/?channels=openess">
       Chat
     </a>
   </h3>

 </div>

</div>



**OpenESS++**  is a network-capable sound server libary mainly for embedded systems and other operatins systems.
OpenESS++ is free and open-source software, and is licensed under the terms of the GNU Lesser General Public License.

<a href="https://www.codacy.com/app/RoseLeBlood/openess?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=RoseLeBlood/openess&amp;utm_campaign=Badge_Grade"><img src="https://api.codacy.com/project/badge/Grade/4f0ba2c68a904b8da2f1d45d5f3596d4"/></a>

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

_create the audio context_
```cpp
#include "ess.h"
#include "ess_context.h"

ess_context context;
ess_error_t error;


#if ESS_PLATFORM_ESP32 == 1
extern "C" void app_main() {
#else
int main() {
#endif
  error = context.create(ESS_BACKEND_NAME_NULL, ESS_FORMAT_STEREO_44100_24);
  ESS_ERROR(error);

  for(;;)  { ess_platform_sleep(10); }
}
```

_probe backends_
```cpp

#include "ess.h"
#include "ess_context.h"

ess_error_t error;

void probe_backend(ess_backend* backend) {

 printf("Probe backend: %s ----------------------------------------------------\n", backend->get_name() );

 for(int y = 0; y < ESS_FORMAT_MAX; y++)  {
  error = backend->probe(  (ess_format_t) y);

   // ++ => support | !! => no support
    printf("\t\t  %s (%s)   \n", (error == ESS_OK) ? "++" : "!!" ,
      ess_format_to_string( (ess_format_t)(y)) );
   }
}

#if ESS_PLATFORM_ESP32 == 1
extern "C" void app_main() {
#else
int main() {
#endif
  ess_backend_t& ins = ess_backend_t::Instance();

  for(auto i = ins.get_backends().begin(); i !=  ins.get_backends().end(); ++i ) {
    probe_backend(i->second);
  }

  for(;;)  { ess_platform_sleep(10); }
}

```
_For more examples and usage, please refer to the [Wiki][wiki]

## Current Features (version 0.3-3)

* Powerful core that allows for easy to port
* Powerful socket abscrations layer (SAL)
* Easy to use platform configuration
* mutex, spinlock, task and ringbuffer handling on various platform (current only esp32)
* generic backends: udp, uart and i2s
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
