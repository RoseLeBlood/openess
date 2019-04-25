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


#include "platform/ess_sleep.h"
#include "ess_output_analyzed_module.h"

#include <sstream>


ess_output_analyzed_module::ess_output_analyzed_module(const std::string& name)
  : ess_output_module(name) {
#if ESS_OUTPUT_TIME_ANALYZED == 1
     m_iUpdatesPerSecond = ess_system_format::get_samplerate()  / ESS_DEFAULT_AUDIO_PACKET_SIZE;
     m_iUpdateCounter = 0;
#endif
}
#if ESS_OUTPUT_TIME_ANALYZED == 1
void ess_output_analyzed_module::start_time_analyzed() {
  if (this->m_bActive) {
    m_iStartTick = ess_platform_get_tick_count();
  }
}
void ess_output_analyzed_module::end_time_analyzed() {
  if (this->m_bActive) {
    m_iFinishTick = ess_platform_get_tick_count();

    if(m_iFinishTick > m_iStartTick)	{
      this->m_iClocksUpdate = (m_iFinishTick - m_iStartTick) - 11;
      this->m_iCloocksSecondSum += this->m_iClocksUpdate;

      if(this->m_iClocksUpdate > this->m_iClocksUpdateMax)
        this->m_iClocksUpdateMax = this->m_iClocksUpdate;

      if(this->m_iClocksUpdate < this->m_iClocksUpdateMin)
        this->m_iClocksUpdateMin = this->m_iClocksUpdate;

      if(m_iUpdateCounter == (m_iUpdatesPerSecond - 1)) {
        m_iClocksUpdateMax = m_iClocksUpdate;			//Reset max
        m_iClocksUpdateMin = m_iClocksUpdate;			//Reset min
        m_iCloocksSecond = m_iCloocksSecondSum;
        m_iCloocksSecondSum = 0;
      }

    } //   if(finishTick > startTick)
  } else {
    m_iClocksUpdate = 0;
  } // if (this->m_bActive)

  m_iUpdateCounter++;
  if(m_iUpdateCounter == m_iUpdatesPerSecond)
    m_iUpdateCounter = 0;
}

std::string ess_output_analyzed_module::get_formated_states() {
  std::ostringstream ss;

  int clocks, clocksMax, clocksSec;
  float load, loadMax, loadSec;

  const float maxTicksPerUpdate = (((float)F_CPU) / 44100.0f) * 128.0f;

  clocks = m_iClocksUpdateMin;
  clocksMax = m_iClocksUpdateMax;
  clocksSec = m_iCloocksSecond;

  load = 100.0f * ((float)clocks / maxTicksPerUpdate);
  loadMax = 100.0f * ((float)clocksMax / maxTicksPerUpdate);
  loadSec = 100.0f * ((float)clocksSec/((float)F_CPU));

  if (this->m_bActive) {
    ss << get_name() << " ld:  " << load << " cl: " << clocks << " cla: " << loadMax << " ldsec: " << loadSec
        << " clsec: " << clocksSec << std::endl;
  } else {
    ss << get_name() << " ld:  " << "-" << " cl: " << "-" << " cla: " << "-" << " ldsec: " << "-"
        << " clsec: " << "-" << std::endl;
  }

  return ss.str();
}
#endif
