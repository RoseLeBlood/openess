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
 * @file ess_time_analyzed_module.h
 * @author Anna Sopdia Schröck
 * @date 30 Januar 2019
 * @brief ESS time analyzed ouput module
 *
 *
 */
 /**
 * @addtogroup stream
 * @{
 */
 #ifndef __ESS_OUTPUT_ANALYZED_MODULE_H__
 #define __ESS_OUTPUT_ANALYZED_MODULE_H__

#include "ess_module.h"

class ess_time_analyzed_module : public ess_module {
public:
  ess_time_analyzed_module(const std::string& name);
  virtual ~ess_time_analyzed_module() { }

#if ESS_TIME_ANALYZED_MODULE == 1

  uint32_t get_time() { return m_iClocksUpdate; }
  uint32_t get_time_max() { return m_iClocksUpdateMax; }
  uint32_t get_time_min() { return m_iClocksUpdateMin; }
  uint32_t get_time_per_seconds() { return m_iCloocksSecond; }

  uint32_t get_time_per_seconds_sum() { return m_iCloocksSecondSum; }


  virtual std::string get_formated_states();
protected:
  virtual void start_time_analyzed();
  virtual void end_time_analyzed();
protected:
  uint32_t m_iClocksUpdate;
	uint32_t m_iClocksUpdateMax;
	uint32_t m_iClocksUpdateMin;
	uint32_t m_iCloocksSecond;
  uint32_t m_iCloocksSecondSum;

  int32_t m_iUpdatesPerSecond;
  int32_t m_iUpdateCounter;
private:
  uint32_t m_iStartTick;
  uint32_t m_iFinishTick;
#endif
};

 #endif
 /**
 * @}
 */
