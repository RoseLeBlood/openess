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
 * @file backend.h
 * @author Anna Sopdia Schröck
 * @date 30 Januar 2019
 * @brief basic backend interface for user and system backends
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



class ess_backend : public ess_audio_stream {
public:
  ess_backend() { }
  ess_backend(unsigned char ninput, ess_audio_block_t **iqueue, const std::string& name) :
    ess_audio_stream(ninput, iqueue, name) {  m_isUsed = false; }

  virtual ~ess_backend() { }

  virtual ess_error_t probe(ess_format_t format) = 0;
  virtual ess_error_t open() {m_isUsed = true;  return ESS_OK; }
  virtual ess_error_t close() {m_isUsed = false;  return ESS_OK; }


  virtual const char* get_info() = 0;

  virtual bool is_used() { return m_isUsed; }

  virtual int get_blksize() { return ESS_BUF_SIZE ; }
protected:
  bool m_isUsed;
};

/**
* @}
*/


#endif
