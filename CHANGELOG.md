
## Release History
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
