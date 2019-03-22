/****************************************************************************
 * Copyright (C) 2019 by Anna Sopdia Schröck                                *
 *                                                                          *
 * This file is part of ess.                                                *
 *                                                                          *
 *   ess is free software: you can redistribute it and/or modify it         *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   ess is distributed in the hope that it will be useful,                 *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Box.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/

#include "config.h"

#ifdef ESS_ENABLE_OUTMODULE_UDPLITE
#include "platform/generic/ess_udplite_output_module.h"
#include "platform/ess_sleep.h"

ess_udplite_output_module::ess_udplite_output_module()
: ess_output_module(ESS_MODULE_OUT_UDPLITE) {

  ess_output_module::add_channel(std::string(ESS_MODULE_OUT_UDPLITE) + std::string("_left"),
    ESS_AUDIO_CHANNEL_LEFT);
  ess_output_module::add_channel(std::string(ESS_MODULE_OUT_UDPLITE) + std::string("_right"),
    ESS_AUDIO_CHANNEL_RIGHT);

  m_bActive = true;
}
ess_error_t ess_udplite_output_module::add_channel(std::string name, ess_audio_channel channel) {
  return ESS_ERROR;
}

ess_error_t ess_udplite_output_module::add_channel(ess_input_channel* channel) {
  return ESS_ERROR;
}

ess_udplite_output_module::~ess_udplite_output_module() { }


ess_error_t ess_udplite_output_module::update(void)  {
  ess_automux_t lock(m_mutex);
  if(!m_bActive) { ess_platform_sleep(1); return ESS_ERROR; }

  bool blocked = false;

   m_iBuffer[1] = new int32_t[ESS_DEFAULT_AUDIO_PACKET_SIZE];
   m_iBuffer[0] = new int32_t[ESS_DEFAULT_AUDIO_PACKET_SIZE];

   memset(m_iBuffer[1], 0, ESS_DEFAULT_AUDIO_PACKET_SIZE);
   memset(m_iBuffer[0], 0, ESS_DEFAULT_AUDIO_PACKET_SIZE);

   if(m_iBuffer[1] == NULL || m_iBuffer[0] == NULL) return ESS_ERROR_OUTOFMEM;

   int red_l = read(ESS_AUDIO_CHANNEL_LEFT,    m_iBuffer[0], 0, ESS_DEFAULT_AUDIO_PACKET_SIZE);
   int red_r = read(ESS_AUDIO_CHANNEL_RIGHT, m_iBuffer[1], 0, ESS_DEFAULT_AUDIO_PACKET_SIZE);


   if(red_l != -1 && red_r != -1)  {
      switch( ess_format_get_bits(ESS_DEFAULT_SERVER_FORMAT) ) {
        case 16:
          for(int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
            int16_t sample[2];
              sample[0] = (m_iBuffer[0]) ?  (int16_t)(m_iBuffer[0][i] * 32767.0f) : 0;
              sample[1] = (m_iBuffer[1]) ?  (int16_t)(m_iBuffer[1][i] * 32767.0f) : 0;

              m_iSampleBuffer[i] = (((sample[1]+ 0x8000)<<16) | ((sample[0]+ 0x8000) & 0xffff));

          }
          break;
        case 24:
          for(int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
              m_iSampleBuffer[i*2 + 1] = (m_iBuffer[0]) ? (-((int32_t)(m_iBuffer[0][i] * 8388608.0f))) << 8 : 0;
              m_iSampleBuffer[i*2] = (m_iBuffer[1]) ?  (-((int32_t)(m_iBuffer[1][i] * 8388608.0f))) << 8 : 0;
          }
          break;
        case 32:
          for(int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
              m_iSampleBuffer[i*2 + 1] = (m_iBuffer[0]) ?  ((int32_t)(m_iBuffer[0][i] * 1073741823.0f)) : 0;
              m_iSampleBuffer[i*2] = (m_iBuffer[1]) ?  ((int32_t)(m_iBuffer[1][i] * 1073741823.0f)) : 0;
          }
          break;
        default:
          break;
      }
   } else {
     printf("blocked\n");
     blocked = true;
   }


   if(!blocked) {
    size_t totalBytesWritten = 0;
    size_t bytesWritten = 0;
    for(;;) {
      bytesWritten = m_iClient.sendto(m_iSampleBuffer,  (ESS_DEFAULT_AUDIO_PACKET_SIZE * sizeof(uint32_t)),
                                                            ESS_OUT_UDP_SENDTO_HOST,
                                                            ESS_OUT_UDPLITE_SENDTO_PORT);

      totalBytesWritten += bytesWritten;
      if(totalBytesWritten >= (ESS_DEFAULT_AUDIO_PACKET_SIZE * sizeof(uint32_t)))
        break;
      vPortYield();
    }
  } else {
    ess_platform_sleep(1);
  }

    if (m_iBuffer[1]) delete m_iBuffer[1];
    if (m_iBuffer[0]) delete m_iBuffer[0];

    return ESS_OK;
}
#endif
