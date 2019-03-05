#include "ess_audio_system.h"

ess_audio_system::ess_audio_system()
  : ess_task(ESS_DEFAULT_SERVER_NAME, this, 4096) {

}
ess_error_t   ess_audio_system::open_backend(const std::string name, ess_backend* bkd) {
  return open_backend(name, ESS_DEFAULT_SERVER_FORMAT, bkd);
}
ess_error_t  ess_audio_system::open_backend(const std::string name, ess_format_t format, ess_backend* bkd) {
  if(bkd == NULL) return ESS_ERROR_NULL;

  bkd =  ess_platform::Instance().get_backend(name);
  if(bkd == NULL) return ESS_ERROR_NULL;

  return bkd->open();
}
ess_audio_conections ess_audio_system::connect (ess_backend& source, ess_audio_channel_t sourceOutput,
  ess_backend& destination, ess_audio_channel_t destinationInput){
    
    return ess_audio_conections(source, (unsigned char)sourceOutput, destination, (unsigned char)destinationInput);
}

void ess_audio_system::onTask(ess_task* self, void* userdata) {
  for(;;)  { ess_audio_stream::update_all(); }
}
