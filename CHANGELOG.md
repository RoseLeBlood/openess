
## Release History
* 0.85.1:
  - add lib/tiny-http libary
  - add is_equels to ip4 and ip6 address class
* 0.85.0:
  - remove old socket system
  - add ess_ipaddress , ess_ip4address, ess_ip6address class
  - add ess_endpoint, ess_ip_endpoint4_t, ess_ip_endpoint6_t
  - add ess_sockets#: inet, inet_stream - ip4/ip6
* 0.8.21:
  - reorder header
  - rename ess_inout_module to ess_effect
  - new base from ess_effect is ess_input_module
  - add ess_dsp_multiply - simple DSP with 2 Inputs and 1 Output (InA * InB = Out)
  - add ess_dsp_multiplexer - simple DSP with 1 Inputs and 2 Output (OutB = In; OutA = In)
  - add ess_channel: virtual bool is_connected
* 0.8.11:
  - call ess_audio_memory_map in ess_platform creating - bug fix
  - update ref implatierung esp32 debug output
  - add ess_debug.h helper functions and example for  ess_output_analyzed_module and the configs ESS_PLATFORM_MONTORING, ESS_OUTPUT_TIME_ANALYZED
* 0.8.10:
  - add ess_error_t ess_task::start(uint32_t core)
  - add ess_audio_block_t
  - update read functions in channel and modules virtual unsigned int  read(ess_audioblock_t *block, unsigned int offset)
  - add memory map for ess_audio_block_t
  - add ess_output_analyzed_module - output module with time analyzed
  - add new configs and reoder:
    - ESS_MAX_AUDIO_MEMORY 163840,
    - ESS_MEMORY_MAP_DEBUG
    - ESS_PLATFORM_MONTORING 1 /**< when set then useble get_cpu_max and get_cpu_load*/
    - ESS_OUTPUT_TIME_ANALYZED
* 0.8.01:
  - add  class ess_stereo_simple_buffer_output_module
    mix floated audio data to a simple integer buffer stereo
  - ess_esp32i2s_output_module changes:
    basic class ess_stereo_simple_buffer_output_module
    ess_esp32uart_output_module changes:
      basic class ess_stereo_simple_buffer_output_module
  - add class ess_system_format:
    static class holder for formart handling
  - ess_platform_esp32 remove:
    get_bits, get_samplerate, get_channels functions and move it to ess_system_format
  - ess_format add:
      ess_format_from_string(const char*)
      remove issus
  - ess_i2s_controller esp32:
      remove issus
      get_format
  - ess_format_t add:
      2.1, Quad , 5.1, 7.1 Formats
* 0.8.00:
  - add udplite output module
  - start esp32 refecrence implantierung (private git - public in the future)
  - version update to 0.8
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
  - add ess_backend::get_blksize
  - add config ESS_BUF_COUNT 4
  - add config ESS_BUF_SIZE      1024
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
* 0.3
  - update platform abstraction layer
  - add mutex, task and spinlock functions - task using mutex on esp32 platforms
  - add examples
* 0.2
  - rename headers
  - add platform abstraction layer
* 0.0.1
  - Work in progress
