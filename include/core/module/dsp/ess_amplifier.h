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
 * @file ess_amplifier.h
 * @author Anna Sopdia Schröck
 * @date 11 März 2019
 * @brief ESS ampliefer  module
 *
 *
 */
 /**
 * @addtogroup dsp
 * @{
 */
#ifndef _ESS_AMPLIFIER_H_
#define _ESS_AMPLIFIER_H_

#include "ess_effect.h"

/**
  * @brief basic ampliefer module
  * basic ampliefer module with  input and  output
  */
class ess_amplifier : public ess_effect {
public:
  ess_amplifier();
  ess_amplifier(const std::string& name);

  void set_gain(float n);
  void set_gain_db(float db);

  float get_gain();
  float get_gain_db();
protected:
  virtual unsigned int do_effect(ess_audioblock_t& block, unsigned int offset, unsigned int size,
    ess_audio_channel id);
private:
	float m_fMultiplier;
};

#endif
/**
* @}
*/
