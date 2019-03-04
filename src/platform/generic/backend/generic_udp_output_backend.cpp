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

/**
 * @file generic_udp_output_backend.cpp
 * @author Anna Sopdia Schröck
 * @date 20 Februar 2019
 * @brief the basic udp backend class
 * this is a udp backend
 */

#include "config.h"
#ifdef ESS_ENABLE_BACKEND_OUT_UDP
#include "platform/generic_udp_output_backend.h"

generic_udp_output_backend::generic_udp_output_backend() : ess_backend(2, m_pInputQueueArray, ESS_BACKEND_NAME_OUT_UDP) {

}
ess_error_t generic_udp_output_backend::probe(ess_format_t format) {
  switch (format) {
    case ESS_FORMAT_MONO_44100_32 :
    case ESS_FORMAT_MONO_48000_32 :
    case ESS_FORMAT_MONO_96000_32 :
    case ESS_FORMAT_STEREO_44100_32 :
    case ESS_FORMAT_STEREO_48000_32 :
    case ESS_FORMAT_STEREO_96000_32 :
      return ESS_ERROR_WRONG_FORMAT;
    default:
      return ESS_OK;
  }

}
ess_error_t generic_udp_output_backend::open()  {
  #if ESS_BACKEND_UDP_PROTOCOL == ESS_PROTOCOL_UDP
    #if ESS_DEFAULT_SERVER_FAMILY == ESS_FAMILY_IP4
      m_pClient = new ess_inet_dram_client_ip4();
    #else
      m_pClient = new ess_inet_dram_client_ip6();
    #endif  // ESS_DEFAULT_SERVER_FAMILY == ESS_FAMILY_IP4
  #elif ESS_BACKEND_UDP_PROTOCOL == ESS_PROTOCOL_UDP_LITE
    #if ESS_DEFAULT_SERVER_FAMILY == ESS_FAMILY_IP4
      m_pClient = new ess_inet_dramlite_client_ip4();
    #else
      m_pClient = new ess_inet_dramlite_client_ip6();
    #endif  // ESS_DEFAULT_SERVER_FAMILY == ESS_FAMILY_IP4
  #endif //ESS_BACKEND_UDP_PROTOCOL == ESS_PROTOCOL_UDP

  if(m_pClient == 0) return ESS_ERROR_OUTOFMEM;


  return  m_pClient->is_socket() && ess_backend::open() ? ESS_OK : ESS_ERROR;

}


ess_error_t generic_udp_output_backend::close() {
  if(m_pClient == 0) return ESS_ERROR;

  return ess_backend::close();
}


unsigned int generic_udp_output_backend::send_packet(const void* data, unsigned int size) {
  if(m_pClient == 0) return -1;

  return m_pClient->sendto(data, size,  ESS_BACKEND_UDP_SENDTO_HOST,
    ESS_BACKEND_UDP_SENDTO_PORT);
}

ess_error_t  generic_udp_output_backend::update(void) {
	ess_audio_block_t *block_left, *block_right;

	if(m_isUsed) {
		block_left = receive_read_only(0);  // input 0
		block_right = receive_read_only(1); // input 1

		switch( ess_format_get_bits(m_eFormat) ) {
			case 16:
				for(int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
					int16_t sample[2];
						sample[0] = (block_left) ?  (int16_t)(block_left->data[i] * 32767.0f) : 0;
						sample[1] = (block_right) ?  (int16_t)(block_right->data[i] * 32767.0f) : 0;

					  m_iSampleBuffer[i] = (((sample[1]+ 0x8000)<<16) | ((sample[0]+ 0x8000) & 0xffff));
				}
				break;
			case 24:
				for(int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
						m_iSampleBuffer[i*2 + 1] = (block_left) ? (-((int32_t)(block_left->data[i] * 8388608.0f))) << 8 : 0;
						m_iSampleBuffer[i*2] = (block_right) ?  (-((int32_t)(block_right->data[i] * 8388608.0f))) << 8 : 0;
				}
				break;
			case 32:
				for(int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
						m_iSampleBuffer[i*2 + 1] = (block_left) ?  ((int32_t)(block_left->data[i] * 1073741823.0f)) : 0;
						m_iSampleBuffer[i*2] = (block_right) ?  ((int32_t)(block_right->data[i] * 1073741823.0f)) : 0;
				}
				break;
			default:
				break;
		}

		size_t totalBytesWritten = 0;
		size_t bytesWritten = 0;
		for(;;) {
			switch( ess_format_get_bits(m_eFormat) ) {
				case 16:
					bytesWritten = send_packet(&m_iSampleBuffer, (ESS_DEFAULT_AUDIO_PACKET_SIZE * sizeof(uint32_t)) );		//Block but yield to other tasks
					break;
				case 24:
				case 32:
          bytesWritten = send_packet(m_iSampleBuffer, (ESS_DEFAULT_AUDIO_PACKET_SIZE * sizeof(uint32_t)) * 2);
					break;
				default:
					break;
			}
			totalBytesWritten += bytesWritten;
			if(totalBytesWritten >= (ESS_DEFAULT_AUDIO_PACKET_SIZE * sizeof(uint32_t)))
				break;
		}

		if (block_left) release(block_left);
		if (block_right) release(block_right);
	}
  return ESS_OK;
}
#endif