**OpenESS 0.6.04**   is a network-capable sound server libary mainly for embedded systems and other operatins systems.
OpenESS is free and open-source software, and is licensed under the terms of the GNU Lesser General Public License.

<a href="https://www.codacy.com/app/RoseLeBlood/openess?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=RoseLeBlood/openess&amp;utm_campaign=Badge_Grade"><img src="https://api.codacy.com/project/badge/Grade/4f0ba2c68a904b8da2f1d45d5f3596d4"/></a>
<img src="https://img.shields.io/github/license/RoseLeBlood/Openess.svg"/>
<img src="https://img.shields.io/github/last-commit/roseleblood/openess.svg"/>
<a href="https://twitter.com/padersophia">
<img src="https://img.shields.io/twitter/follow/padersophia.svg"></a>


_For informations, examples and usage, please refer to the [Wiki][wiki]_

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
