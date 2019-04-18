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
#include "platform/generic/ess_udplite_stereo_output_module.h"
#include "platform/ess_sleep.h"

ess_udplite_stereo_output_module::ess_udplite_stereo_output_module()
: ess_stereo_simple_buffer_output_module(ESS_MODULE_OUT_UDPLITE) {
  m_bActive = true;
}
ess_udplite_stereo_output_module::~ess_udplite_stereo_output_module() { }

size_t ess_udplite_stereo_output_module::send_simple_buffer_to_device(int32_t* simple_buffer, size_t offset, size_t size) {
  return m_iClient.sendto(simple_buffer,  (size), ESS_OUT_UDP_SENDTO_HOST,   ESS_OUT_UDPLITE_SENDTO_PORT);
}

#endif
