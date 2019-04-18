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
  ess_audioblock_t* pBlock;
  uint32_t readed;

  if(!m_bActive) { ess_platform_sleep(1); return ESS_ERROR; }

  pBlock = ess_mem_alloc();

  for(int i=0; i <= ESS_CHANNEL_FORMAT_7POINT1; i++) {
    readed = read(ESS_AUDIO_CHANNEL_LEFT,    pBlock, 0);
  }

  ess_mem_free(pBlock);

  ess_platform_sleep(1);
  return ESS_OK;
}
