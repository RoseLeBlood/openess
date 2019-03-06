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
 * @file ess_output_stream.h
 * @author Anna Sopdia Schröck
 * @date 30 Januar 2019
 * @brief ESS generic ouput stream
 *
 *
 */
 /**
 * @addtogroup backend
 * @{
 */
#ifndef __ESS_BACKEND_H__
#define __ESS_BACKEND_H__

#include "ess.h"
#include "ess_error.h"
#include "ess_format.h"

#include "ess_audio_stream.h"



class ess_output_stream: public ess_audio_stream {
public:
  ess_output_stream() { }
  ess_output_stream(unsigned char ninput, ess_audio_block_t **iqueue, const std::string& name) :
    ess_audio_stream(ninput, iqueue, name) {  m_isUsed = false; }

  virtual ~ess_output_stream() { }

  virtual ess_error_t probe(ess_format_t format) { return ESS_ERROR; }
  virtual ess_error_t open() {m_isUsed = true;  return ESS_OK; }
  virtual ess_error_t close() {m_isUsed = false;  return ESS_OK; }


  virtual const char* get_info() { return ""; }
  virtual bool is_used() { return m_isUsed; }
  virtual int get_blksize() { return ESS_BUF_SIZE ; }

  virtual ess_error_t update(void) { return ESS_ERROR; }
protected:
  bool m_isUsed;
};

/**
* @}
*/


#endif
