#include "ess_audio_system.h"

ess_audio_system::ess_audio_system()
  : ess_task(ESS_DEFAULT_SERVER_NAME, this, 4096) {

}
ess_error_t   ess_audio_system::open_device(const std::string name, ess_audio_stream* bkd) {
  return open_device(name, ESS_DEFAULT_SERVER_FORMAT, bkd);
}
ess_error_t  ess_audio_system::open_device(const std::string name, ess_format_t format, ess_audio_stream* bkd) {
  if(bkd == NULL) return ESS_ERROR_NULL;

  bkd =  ess_platform::Instance().open_device(name);
  if(bkd == NULL) return ESS_ERROR_NULL;



  ess_error_t error =  bkd->open();
  printf("%s\n", bkd->get_info().c_str());

  return error;
}

ess_audio_conections  ess_audio_system::connect (ess_audio_stream& source, ess_audio_stream& destination,
  ess_audio_channel_t channel) {
    return ess_audio_conections(source, channel, destination, channel);
}

ess_audio_conections ess_audio_system::connect (ess_audio_stream& source, ess_audio_channel_t sourceOutput,
  ess_audio_stream& destination, ess_audio_channel_t destinationInput){

    return ess_audio_conections(source, sourceOutput, destination, destinationInput);
}
ess_error_t ess_audio_system::add_input_stream(ess_audio_stream* bkd) {
  if(bkd == NULL) return ESS_ERROR_NULL;

  if(m_pRootStream == NULL) {
    m_pRootStream = bkd;
  }
  else {
    ess_audio_stream *p;
    for (p=m_pRootStream; p->m_pNextUpdate; p = p->m_pNextUpdate) ;
      p->m_pNextUpdate = bkd;
  }
  return ESS_OK;
}


void ess_audio_system::onTask(ess_task* self, void* userdata) {
  for(;;)  {
    ess_audio_stream *p;

  	for (p = m_pRootStream; p; p = p->m_pNextUpdate) {
  		if (p->m_bActive) {
  			if(p->m_bBlocking || !p->m_bInit){
  				p->update();
  			}
  			else{
  				//m_pUpdateMutex.lock();
  				p->update();
  				//m_pUpdateMutex.unlock();
  			}
  		}
  	}
  	if(!p->m_bBlockingObjectRun)
  		ess_platform_sleep(10);		//If user is calling update_all but there aren't any streams controlling the timing, this'll stop 100% CPU

  }
}
