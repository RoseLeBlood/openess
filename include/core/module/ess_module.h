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
#include "../../task/ess_autolock.h"

#include "../../ess_audio_buffer_stream.h"

/**
  * @brief basic class for module
  *
  */
  // +--------------+<br>
  //  |                   |<br>
  //  |                   |<br>
  // +------------- +<br>
class ess_module  : public ess_object  {
public:
  ess_module() { }
  ess_module(const std::string& name)
    : ess_object(name), m_bActive(false) { m_mutex.create(); }

  virtual ~ess_module() { set_active(false); m_mutex.destroy(); }

  virtual bool is_active() {
    ess_automux_t lock(m_mutex);
    return m_bActive;
  }
  virtual ess_error_t set_active(bool active)  {
    ess_automux_t lock(m_mutex);
    m_bActive = active; return ESS_OK;
   }

   virtual unsigned int read(ess_audio_channel id, ess_audioblock_t& block, unsigned int offset) = 0;
protected:
  bool m_bActive;
  ess_mutex m_mutex;
};

/**
* @}
*/


#endif
