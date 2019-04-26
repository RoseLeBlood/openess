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
#include "platform/generic/ess_null_output_module.h"
#include "platform/ess_sleep.h"

ess_null_output_module::ess_null_output_module()
  : ess_output_module(ESS_NULL_OUTPUT_NAME) { }

ess_null_output_module::~ess_null_output_module() { }

ess_error_t ess_null_output_module::update(void) {
  #if ESS_OUTPUT_TIME_ANALYZED == 1
    start_time_analyzed();
  #endif

  if(m_bActive) {


    for(int i=0; i <= ESS_CHANNEL_FORMAT_7POINT1; i++) {
      ess_audioblock_t* buffer = ess_audioblock_alloc();
      read(ESS_AUDIO_CHANNEL_LEFT,    buffer, 0);
      ess_audioblock_relese(buffer);
    }
  }

  #if ESS_OUTPUT_TIME_ANALYZED == 1
     end_time_analyzed();
  #endif
  return ESS_OK;
}
