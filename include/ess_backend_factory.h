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
 * @file ess_backend_factory.h
 * @author Anna Sopdia Schröck
 * @date 18 Februar 2019
 * @brief Contains backend factory template class and backend root class
 *
 *
 */

#ifndef __ESS_BACKEND_FACTORY_H__
#define __ESS_BACKEND_FACTORY_H__

#include "ess_backend.h"
#include <map>

#include "platform/generic_null_backend.h"

/**
* @addtogroup backend
* @{
*/

class ess_backend_platform {
public:
  ess_backend_platform() {
    add_backend(new generic_null_backend());


  }
  virtual void create() = 0;
  virtual ess_backend* get_backend(const char* name);

  virtual std::string get_platform_name() = 0;
  virtual std::string get_factory_creater() = 0;

  virtual  bool add_backend(ess_backend* backend);


  std::map<std::string, ess_backend*>& get_backends() { return m_lBackends; }
protected:
  std::map<std::string, ess_backend*> m_lBackends;
};
/**
 * @brief ess backend factory
 *
 * Embedded Sound System Backend factory. Backend vtable
 */
template <class BACKEND>
class ess_backend_factory {
public:
  static ess_backend_factory<BACKEND>& Instance() {
    if(m_pInstance == nullptr) {
      m_pInstance = new ess_backend_factory<BACKEND>();
    }
    return *m_pInstance;
  }
public:
  ess_backend* get_backend(const char* name)  {
    return m_pPlatform.get_backend(name);
  }
  std::map<std::string, ess_backend*>& get_backends() {
    return m_pPlatform.get_backends();
  }
private:
  ess_backend_factory() {
    m_pPlatform.create();
  }
private:
  static ess_backend_factory<BACKEND> *m_pInstance ;
  BACKEND m_pPlatform;
};
template <class BACKEND>
ess_backend_factory<BACKEND>* ess_backend_factory<BACKEND>::m_pInstance = 0;
#endif
/**
* @}
*/
