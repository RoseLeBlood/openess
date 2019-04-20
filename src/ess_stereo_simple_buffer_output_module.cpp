#include "ess.h"
#include "ess_stereo_simple_buffer_output_module.h"


ess_stereo_simple_buffer_output_module::ess_stereo_simple_buffer_output_module(const std::string& name)
  : ess_output_analyzed_module(name) {


    ess_output_module::add_channel(std::string(name) + std::string("_left"),
      ESS_AUDIO_CHANNEL_LEFT);
    ess_output_module::add_channel(std::string(name) + std::string("_right"),
      ESS_AUDIO_CHANNEL_RIGHT);




}
ess_stereo_simple_buffer_output_module::~ess_stereo_simple_buffer_output_module() {
  ess_automux_t lock(m_mutex);

  m_bActive = false;

}
ess_error_t ess_stereo_simple_buffer_output_module::add_channel(std::string name, ess_audio_channel channel) {
  return ESS_ERROR;
}
ess_error_t ess_stereo_simple_buffer_output_module::add_channel(ess_input_channel* channel) {
  return ESS_ERROR;
}
ess_error_t ESS_IRAM_ATTR ess_stereo_simple_buffer_output_module::update(void) {
  ess_automux_t lock(m_mutex);

#if ESS_OUTPUT_TIME_ANALYZED == 1
  start_time_analyzed();
#endif

   if(!m_bActive) { ess_platform_sleep(1); return ESS_ERROR; }

   m_iBuffer[1] = ess_mem_alloc();
   m_iBuffer[0] = ess_mem_alloc();

   bool blocked = false;

    int red_l = read(ESS_AUDIO_CHANNEL_LEFT,    m_iBuffer[0], 0);
    int red_r = read(ESS_AUDIO_CHANNEL_RIGHT, m_iBuffer[1], 0);


    if(red_l != -1 && red_r != -1)  {
   		switch( ess_system_format::get_bits() ) {
   			case 16:
   				for(int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
   					int16_t sample[2];
   						sample[0] = (m_iBuffer[0]->data) ?  (int16_t)(m_iBuffer[0]->data[i] * 32767.0f) : 0;
   						sample[1] = (m_iBuffer[1]->data) ?  (int16_t)(m_iBuffer[1]->data[i] * 32767.0f) : 0;

   					  m_iSampleBuffer[i] = (((sample[1]+ 0x8000)<<16) | ((sample[0]+ 0x8000) & 0xffff));

   				}
   				break;
   			case 24:
   				for(int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
   						m_iSampleBuffer[i*2 + 1] = (m_iBuffer[0]) ? (-((int32_t)(m_iBuffer[0]->data[i] * 8388608.0f))) << 8 : 0;
   						m_iSampleBuffer[i*2] = (m_iBuffer[1]) ?  (-((int32_t)(m_iBuffer[1]->data[i] * 8388608.0f))) << 8 : 0;
   				}
   				break;
   			case 32:
   				for(int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
   						m_iSampleBuffer[i*2 + 1] = (m_iBuffer[0]) ?  ((int32_t)(m_iBuffer[0]->data[i] * 1073741823.0f)) : 0;
   						m_iSampleBuffer[i*2] = (m_iBuffer[1]) ?  ((int32_t)(m_iBuffer[1]->data[i] * 1073741823.0f)) : 0;
   				}
   				break;
   			default:
   				break;
   		}
    } else {
      printf("blocked\n");
      blocked = true;
    }

    ess_mem_free(m_iBuffer[0]);
    ess_mem_free(m_iBuffer[1]);

    if(!blocked) {
     size_t totalBytesWritten = 0;
     size_t bytesWritten = 0;
     for(;;) {
     	bytesWritten = send_simple_buffer_to_device(m_iSampleBuffer, totalBytesWritten,
          (ESS_DEFAULT_AUDIO_PACKET_SIZE * sizeof(uint32_t))  );

      if(bytesWritten > 0 ) {
     	  totalBytesWritten += bytesWritten;
     	  if(totalBytesWritten >= (ESS_DEFAULT_AUDIO_PACKET_SIZE * sizeof(uint32_t)))
     		 break;
       } else {
         ess_platform_sleep(1);
         break;
       }
     	vPortYield();
     }
   } else {
     ess_platform_sleep(1);
   }
#if ESS_OUTPUT_TIME_ANALYZED == 1
   end_time_analyzed();
#endif
   return ESS_OK;
 }
