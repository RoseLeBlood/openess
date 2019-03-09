#include "ess_input_channel.h"
#include <sstream>

ess_input_channel::ess_input_channel()
  : ess_input_channel("ess_input_channel", ESS_AUDIO_CHANNEL_LEFT)  { }

ess_input_channel::ess_input_channel(std::string name)
  : ess_channel(name, ESS_CHANNEL_INPUT, ESS_AUDIO_CHANNEL_LEFT),
    m_pConChannel(NULL)  { }

ess_input_channel::ess_input_channel(std::string name, ess_audio_channel channel )
  : ess_channel(name, ESS_CHANNEL_INPUT, channel),
    m_pConChannel(NULL) { }

 bool ess_input_channel::is_connected() {
   return m_pConChannel != NULL;
 }

 unsigned int ESS_IRAM_ATTR ess_input_channel::read(int32_t* buffer, unsigned int offset, unsigned int size) {
   ess_automux_t lock(m_mutex);
   return is_connected() ? m_pConChannel->read(buffer, offset, size) : -1;
 }

 ess_error_t ess_input_channel::connect(ess_output_channel* channel) {
   ess_automux_t lock(m_mutex);
   if(m_pConChannel != NULL )  return ESS_ERROR_CONNECT;

   m_pConChannel = channel;
   return ESS_OK;
 }
std::string ess_input_channel::to_string() {
  std::ostringstream ss;

  ss  << ess_channel::to_string();
  if(is_connected() ) ss << " <- " <<    m_pConChannel->to_string();

  return ss.str();
}
