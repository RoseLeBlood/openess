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
#include "ess_output_module.h"

#include <list>

template <class T>
class ess_platform_interface : public ess_object  {
  static T* m_pInstance;
public:
  static T& Instance() {
    if(m_pInstance == nullptr) m_pInstance = new T();
    return *m_pInstance;
  }
protected:
  ess_platform_interface(const std::string name)  : ess_object(name) { }
public:
  virtual ess_error_t create() {
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

  virtual ess_output_module* create_output(ess_output_type type, std::string controller_name) {
    return create_output(type, controller_name, ESS_DEFAULT_SERVER_FORMAT);
  }

  virtual ess_output_module* create_output(ess_output_type type, std::string controller_name,
    ess_format_t format)  = 0;

  
private:
  std::list<ess_controler*> m_iController;
};

template <class T>
T* ess_platform_interface<T>::m_pInstance = nullptr;
#endif
