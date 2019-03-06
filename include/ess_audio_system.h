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
 * @file ess_audio_system.h
 * @author Anna Sopdia Schröck
 * @date 05 März 2019
 * @brief ess audio system for auto update
 *
 *
 */
 /**
 * @addtogroup stream
 * @{
 */
 #ifndef __OPEN_ESS_AUDIO_SYSTEM_H__
 #define __OPEN_ESS_AUDIO_SYSTEM_H__

#include "ess.h"
#include "ess_task.h"
#include "ess_platform.h"
#include "ess_audio_stream.h"


class ess_audio_system : public ess_task {
public:
  ess_audio_system();

  virtual ess_error_t  open_device(const std::string name, ess_output_stream* bkd);
  virtual ess_error_t  open_device(const std::string name, ess_format_t format, ess_output_stream* bkd);

  virtual ess_audio_conections  connect (ess_audio_stream& source, ess_audio_stream& destination,
    ess_audio_channel_t channel);

  virtual ess_audio_conections  connect (ess_audio_stream& source, ess_audio_channel_t sourceOutput,
		ess_audio_stream& destination, ess_audio_channel_t destinationInput);

  virtual void onTask(ess_task* self, void* userdata);

  virtual ess_format_t get_format() { return ESS_DEFAULT_SERVER_FORMAT; }
  virtual int get_block_size() { return ESS_DEFAULT_AUDIO_PACKET_SIZE; }

private:

};


/**
* @}
*/


#endif
