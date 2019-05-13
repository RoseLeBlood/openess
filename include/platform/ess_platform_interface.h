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
 * @file ess_platform_interface.h
 * @author Anna Sopdia Schröck
 * @date 18 Februar 2019
 * @brief platform backends combiunations with OpenESS
 *
 *
 */
 /**
 * @addtogroup platform
 * @{
 */

 #ifndef __ESS_PLATFORM_INTERFACE_H__
 #define __ESS_PLATFORM_INTERFACE_H__

#include "platform/ess_controler.h"
#include "../core/module/ess_output_module.h"
#include "../ess_singleton_object.h"
#include <list>

void ess_mem_init(unsigned int num, ess_audioblock_t* _static_data);

template <class T, uint8_t NUM_CPUS>
class ess_platform_interface : public ess_singleton_object<T>  {
  friend class ess_singleton_object<T>;
protected:
  ess_platform_interface(const std::string name)  : ess_singleton_object<T>(name) {
    m_pStdDevice = nullptr;
  }
public:
  virtual ess_error_t create(ess_audioblock_t* _static_data = nullptr, unsigned int num = 0) {
    #if ESS_MEMORY_MAP_EXTERN == ESS_ON
    ess_audioblock_create(num, _static_data);
    #else
    ess_audioblock_create();
    #endif

    std::list<ess_controler*>::iterator it;
    for(it = m_iController.begin(); it != m_iController.end(); it++) {
      if( (*it)->is_created() == false )
        if((*it)->setup(0) != ESS_OK) return ESS_ERROR;
    }
    return ESS_OK;
  }

  virtual ess_error_t add_controller(ess_controler* controller) {
    m_iController.push_back(controller);
    return ESS_OK;
  }
  virtual ess_controler* get_controller(std::string name) {
    std::list<ess_controler*>::iterator it;
    for(it = m_iController.begin(); it != m_iController.end(); it++) {
      if( (*it)->get_name() == name )
        return (*it);
    }
    return nullptr;
  }

  virtual ess_output_module* open_output(ess_output_type type, std::string controller_name) {
    ess_output_module* output = create_output(type, controller_name, ESS_DEFAULT_SERVER_FORMAT);
    if(m_pStdDevice == nullptr) m_pStdDevice = output;

    if(output != NULL) {
      m_iOutputs.push_back(output);
    }
    return output;
  }
  virtual ess_output_module* get_std_device() {
    return m_pStdDevice;
  }
  virtual ess_output_module* create_output(ess_output_type type, std::string controller_name,
    ess_format_t format)  = 0;

  #if ESS_PLATFORM_MONTORING == 1
  float get_cpu_load(int cpu) { return (cpu > NUM_CPUS) ?  0 : m_fCPULoad[cpu]; }
  float get_cpu_max(int cpu) { return (cpu > NUM_CPUS) ? 0 : m_fCPULoadMax[cpu]; }
  #endif
protected:
  #if ESS_PLATFORM_MONTORING == 1
  float m_fCPULoad[NUM_CPUS];
  float m_fCPULoadMax[NUM_CPUS];
#endif
private:
  std::list<ess_controler*> m_iController;
  std::list<ess_output_module*> m_iOutputs;
  ess_output_module* m_pStdDevice;
};


#endif
/**
* @}
*/
