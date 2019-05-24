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
 * @file ess_singleton_object.h
 * @author Anna Sopdia Schröck
 * @date 15 Mai 2019
 */
#ifndef _ESP32_PLATFOREM_INSTANCE_H_
#define _ESP32_PLATFOREM_INSTANCE_H_

#include "ess_singleton_object.h"

class esp32_platform_instance : public ess_singleton_object<esp32_platform_instance> {
    ESS_SINGLETON(esp32_platform_instance)
protected:
  esp32_platform_instance()
    : ess_singleton_object() {  m_bWifiReady = false; }
public:
  void set_wifi_ready() { ess_autolock_t lock(*this);  m_bWifiReady = true;}
  bool is_wifi_ready() { ess_autolock_t lock(*this);  return m_bWifiReady; }
private:
  bool  m_bWifiReady;
};

#endif
