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
 * @file ess_platform_esp32.cpp
 * @author Anna Sopdia Schröck
 * @date 30 Januar 2019
 * @brief ess esp32 backend impl.
 *
 */

#include "ess.h"
#include "platform/esp32/ess_platform_esp32.h"
#include "platform/esp32/ess_esp32i2s_output_module.h"
#include "platform/esp32/ess_i2s_controller.h"


#include "platform/generic/ess_null_output_module.h"

#ifdef ESS_ENABLE_OUTMODULE_UDPLITE
#include "platform/generic/ess_udplite_stereo_output_module.h"
#endif

#ifdef ESS_ENABLE_OUTMODULE_UART
#include "platform/esp32/ess_esp32uart_output_module.h"
#endif

#include <esp_freertos_hooks.h>

volatile uint32_t idlectrl1 = 0;
volatile uint32_t idlectrl0 = 0;

void _esp32_platform_montoring_cpu0( void * parameter ) ;
void _esp32_platform_montoring_cpu1( void * parameter ) ;




ess_platform_esp32::ess_platform_esp32()
  : ess_platform_interface<ess_platform_esp32, ESS_CONFIC_MAX_CORES>() {



  #ifdef ESS_ENABLE_BACKEND_OUT_I2S
  add_controller(new ess_i2s_controller());
  #endif
}
ess_error_t ess_platform_esp32::create()  {
  #if ESS_PLATFORM_MONTORING == 1
  esp_register_freertos_idle_hook_for_cpu((esp_freertos_idle_cb_t)_esp32_platform_montoring_cpu0, 1);
  esp_register_freertos_idle_hook_for_cpu((esp_freertos_idle_cb_t)_esp32_platform_montoring_cpu1, 1);
  #endif

  return  ess_platform_interface<ess_platform_esp32, ESS_CONFIC_MAX_CORES>::create();
}
ess_output_module* ess_platform_esp32::create_output(ess_output_type type,
  std::string controller_name,
  ess_format_t format)  {

  ess_output_module* mod = nullptr;
  ess_controler* controller ;

  switch(type) {
    case ESS_OUTPUT_NULL:
      mod = new ess_null_output_module();
      break;
    case ESS_OUTPUT_UART:
      #ifdef ESS_ENABLE_OUTMODULE_UART
      mod = new ess_esp32uart_output_module();
      #endif
      break;
    case ESS_OUTPUT_UDP:
      #ifdef ESS_ENABLE_OUTMODULE_UDPLITE
      mod = new ess_udplite_stereo_output_module();
      #endif
      break;
    case ESS_OUTPUT_I2S:
      #ifdef  ESS_ENABLE_BACKEND_OUT_I2S
      controller = get_controller(controller_name);
      if(controller != NULL)
        mod = new ess_esp32i2s_output_module(controller);
      #endif
      break;

    default:
      mod = nullptr; break;
  }
  return mod;
}


#if ESS_PLATFORM_MONTORING == 1
void _esp32_platform_montoring_cpu1( void * parameter ) {
  const uint32_t cycleCount = 21818182;   //240MHz / 11
  uint32_t t00, t01;

  t00 = xthal_get_ccount();
  for(uint32_t i = 0; i < cycleCount; i++) {
    idlectrl0++;
  }
  t01 = xthal_get_ccount();

  uint32_t cycles_expected = 11 * cycleCount;
  uint32_t cycles_used = t01 - t00;

  ess_platform_esp32::Instance().m_fCPULoad[1] = 100.0f * (cycles_used - cycles_expected) / cycles_used;
  if(ess_platform_esp32::Instance().m_fCPULoad[1] > ess_platform_esp32::Instance().m_fCPULoadMax[1])
    ess_platform_esp32::Instance().m_fCPULoadMax[1] = ess_platform_esp32::Instance().m_fCPULoad[1];
}

void _esp32_platform_montoring_cpu0( void * parameter ) {
  const uint32_t cycleCount = 21818182;   //240MHz / 11
  uint32_t t00, t01;

  t00 = xthal_get_ccount();
  for(uint32_t i = 0; i < cycleCount; i++) {
    idlectrl0++;
  }
  t01 = xthal_get_ccount();

  uint32_t cycles_expected = 11 * cycleCount;
  uint32_t cycles_used = t01 - t00;


  ess_platform_esp32::Instance().m_fCPULoad[0] = 100.0f * (cycles_used - cycles_expected) / cycles_used;
  if(ess_platform_esp32::Instance().m_fCPULoad[0] > ess_platform_esp32::Instance().m_fCPULoadMax[0])
    ess_platform_esp32::Instance().m_fCPULoadMax[0] = ess_platform_esp32::Instance().m_fCPULoad[0];
}
#endif
