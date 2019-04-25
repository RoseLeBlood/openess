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
 * @file ess_debug.h
 * @author Anna Sopdia Schröck
 * @date 20 April 2019
 * @brief inline function for debug
 *
 *
 */
 /**
 * @addtogroup debug
 * @{
 */
#ifndef _ESS_DEBUG_INFO_H_
#define _ESS_DEBUG_INFO_H_

#include "ess_output_analyzed_module.h"
#include "ess_audioblock.h"
#include "ess_platform.h"

#include <sstream>

inline void ess_debug() {
  #if ESS_PLATFORM_MONTORING == 1

  std::cout << ess_platform_millis() <<  " ms uptime" << std::endl;
  for(int i= 0; i < ESS_CONFIC_MAX_CORES; i++) {
    std::cout << "CPU" << i << ": " << ess_platform::Instance().get_cpu_load(i) << " %"
                   << "[ " << ess_platform::Instance().get_cpu_max(i) << " % ]" << std::endl;
  }
  #endif

  #if ESS_OUTPUT_TIME_ANALYZED == 1
  ess_output_analyzed_module* mod = (ess_output_analyzed_module*)ess_platform::Instance().get_std_device();
  #endif

  #if ESS_OUTPUT_TIME_ANALYZED == 1
  if(mod != 0) std::cout  << mod->get_formated_states() << std::endl;
  std::cout << "------------------------------------" << std::endl;
  #endif

  std::cout << "mem: " << ess_audioblock_used() << " /  " <<
  ess_audioblock_max_used() << " / " <<
  ess_audioblock_num() << "\r\n" ;
  std::cout << "------------------------------------" << std::endl;

  if(mod != 0)  mod->update();
  std::cout << "------------------------------------" << std::endl;

  std::cout << "mem: " << ess_audioblock_used() << " /  " <<
  ess_audioblock_max_used() << " / " <<
  ess_audioblock_num() << "\r\n" ;
  std::cout << "------------------------------------" << std::endl;

  #if ESS_OUTPUT_TIME_ANALYZED == 1
  if(mod != 0)  std::cout  << mod->get_formated_states() << std::endl;
  std::cout << "------------------------------------" << std::endl;
  #endif

  ess_platform_sleep(1);
}
/**
* @}
*/
#endif
