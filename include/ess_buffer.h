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
 * @file ess_buffer.h
 * @author Anna Sopdia Schröck
 * @date 23 Februar 2019
 * @brief audio buffer class
 *
 */
 #ifndef _ESS_AUDIO_BUFFER_H_
 #define _ESS_AUDIO_BUFFER_H_

#include "ess_ringbuffer.h"

class ess_buffer : public ess_ringbuffer {
public:
  ess_buffer() { }
  ess_buffer(ess_format_t format) : m_eFormat(format) { }

  ess_format_t get_format() { return m_eFormat; }
protected:
  ess_format_t m_eFormat;
};

#endif
