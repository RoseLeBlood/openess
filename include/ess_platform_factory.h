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
 * @file ess_platform_factory.h
 * @author Anna Sopdia Schröck
 * @date 18 Februar 2019
 * @brief Contains backend factory template class and backend root class
 *
 *
 */

#ifndef __ESS_BACKEND_FACTORY_H__
#define __ESS_BACKEND_FACTORY_H__

#include "ess_output_stream.h"
#include <map>
# include <memory>

#include "platform/generic_null_backend.h"
#ifdef ESS_ENABLE_BACKEND_OUT_UDP
#include "platform/generic_udp_output_backend.h"
#endif
/**
* @addtogroup backend
* @{
*/

class ess_interface_platform {
public:
  ess_interface_platform() {
    add_device(new generic_null_backend());
    #ifdef ESS_ENABLE_BACKEND_UDP
    add_device( new generic_udp_output_backend());
    #endif

  }
  virtual void create() = 0;
  virtual ess_audio_stream*  open_device(const std::string name);

  virtual std::string get_platform_name() = 0;
  virtual std::string get_factory_creater() = 0;

  virtual  bool add_device(ess_audio_stream* backend);


protected:
  std::map<std::string, ess_audio_stream* > m_lBackends;
};
/**
 * @brief ess backend factory
 *
 * Embedded Sound System Backend factory. Backend vtable
 */
template <class T>
class ess_platform_factory {
public:
  using ess_platform_t = T;

  static ess_platform_factory<ess_platform_t>& Instance() {
    if(m_pInstance == nullptr) {
      m_pInstance = new ess_platform_factory<ess_platform_t>();
    }
    return *m_pInstance;
  }
public:
  ess_audio_stream* open_device(const std::string& name)  {
    return m_pPlatform.open_device(name);
  }
  bool add_device(ess_audio_stream* backend) {
    return m_pPlatform.add_device(backend);
  }
  ess_platform_t get_platform() {
    return m_pPlatform;
  }
private:
  ess_platform_factory() {
    m_pPlatform.create();
  }
private:
  static ess_platform_factory<T> *m_pInstance ;
  ess_platform_t m_pPlatform;
};
template <class T>
ess_platform_factory<T>* ess_platform_factory<T>::m_pInstance = 0;
#endif
/**
* @}
*/
