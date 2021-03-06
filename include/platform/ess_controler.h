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
 * @file ess_ontroler.h
 * @author Anna Sopdia Schröck
 * @date 04 März 20119
 * @brief generic platform hardware controller
 *
 *
 */
#ifndef _ESS_PLATFORM_CONTROLER_H_
#define _ESS_PLATFORM_CONTROLER_H_

#include "ess.h"

class ess_controler  : public ess_object {
public:
  ess_controler() : ess_object("ess_controler") { m_bCreated = false; }
  ess_controler(const std::string name)  : ess_object(name) { m_bCreated = false; }

  virtual ~ess_controler() { destroy(0); }

  virtual ess_format_t get_format() { return ESS_DEFAULT_SERVER_FORMAT; }
  virtual int get_bits() { return ess_format_get_bits(get_format()) ; }
  virtual int get_samplerate()  { return ess_format_get_samplerate(get_format()) ; }
  virtual int get_channels()  { return ess_format_get_channels(get_format()) ; }

  virtual ess_error_t setup(int flags) { return ESS_OK; }
  virtual ess_error_t destroy(int flags) { return ESS_OK; }

  virtual unsigned int write(void* buffer, unsigned int offset, unsigned  int size) { return -1; }
  virtual unsigned int read(void* buffer, unsigned int offset, unsigned  int size) { return -1; }

  virtual bool is_created() { return m_bCreated; }
protected:
  bool m_bCreated;
};


#endif
