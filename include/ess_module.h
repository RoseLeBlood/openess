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
 * @file ess_module.h
 * @author Anna Sopdia Schröck
 * @date 08 März 2019
 * @brief ESS generic  module
 *
 *
 */
 /**
 * @addtogroup ess
 * @{
 */
#ifndef __ESS_MODULE_H__
#define __ESS_MODULE_H__

#include "ess.h"

/**
  * @brief basic class for module
  *
  */
  // +--------------+
  //  |                   |
  //  |                   |
  // +------------- +
class ess_module  {
public:
  ess_module() { }
  ess_module(const std::string& name)
    : m_strName(name), m_bActive(false), m_bInit(false) { }

  virtual ~ess_module() { close(); }

  virtual ess_error_t close() { m_bActive = m_bInit =  false; return ESS_OK; }
  virtual ess_error_t open() {  m_bInit =  true; return ESS_OK; }

  virtual bool is_init() { return m_bInit; }
  virtual bool is_active() { return m_bActive; }

  virtual ess_error_t set_active(bool active)  {
     if(!m_bInit) return ESS_ERROR;  m_bActive = active; return ESS_OK;
   }

   virtual std::string get_name() { return m_strName; }

   virtual unsigned int read(int32_t* buffer, unsigned int offset, unsigned int size, ess_audio_channel id) = 0;
protected:
  std::string m_strName;
  bool m_bActive;
  bool m_bInit;
};

/**
* @}
*/


#endif
