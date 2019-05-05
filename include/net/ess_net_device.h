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
 * @file ess_net_device.h
 * @author Anna Sopdia Schröck
 * @date 05 Mai 2019
 */
 #ifndef _ESS_NET_INTERFACE_DEVICE_H_
 #define _ESS_NET_INTERFACE_DEVICE_H_

#include "ess_ip6address.h"

enum ess_net_device_type {
  ESS_NET_DEVICE_WIFI,
  ESS_NET_DEVICE_ETHRNET,
  ESS_NET_DEVICE_MOBILE
};
enum ess_net_device_status {
  ESS_NET_DEVICE_STATUS_UP = 0x0001,
  ESS_NET_DEVICE_STATUS_DOWN = 0x0000,
};
class ess_net_device : public ess_object {
public:
  struct if_address {
    ess_ip4address local_address4;
    ess_ip4address sub_net_mask;
    ess_ip4address dns_address4;

    ess_ip6address local_address6;
    ess_ip6address dns_address6;
  };
  ess_net_device(ess_net_device_type type, std::string name)
    : ess_object(name) { m_tType = type;  on_start_up(); }

  virtual ess_error_t initialize() = 0;
  virtual ess_error_t set_status(ess_net_device_status nstet) = 0;
  virtual ess_error_t change_if_address(if_address if_addr) = 0;

//-------get_ip4------------------------------------
  virtual ess_ip4address get_local_ip4() const
    { return m_if_address.local_address4; }

  virtual ess_ip4address get_sub_net_mask() const
    { return m_if_address.sub_net_mask; }

  virtual ess_ip4address get_dns_ip4() const
    { return m_if_address.dns_address4; }
//-------get_ip6------------------------------------
  virtual ess_ip6address get_local_ip6() const
    { return m_if_address.local_address6; }

  virtual ess_ip6address get_dns_ip6() const
    { return m_if_address.dns_address6; }
//-------get_misc------------------------------------
  virtual ess_net_device_status get_status()
    { return m_fStatus; }

  virtual ess_net_device_type get_type()
    { return m_tType; }
//-------set_ip4------------------------------------
  virtual ess_error_t set_local_ip4(const ess_ip4address value)  {
    if(m_if_address.local_address4 == value ) return ESS_OK;
    if_address  new_address = m_if_address;
    new_address.local_address4 = value;
    return change_if_address(new_address);
  }
  virtual ess_error_t set_sub_net_mask(const ess_ip4address value)  {
    if(m_if_address.sub_net_mask == value ) return ESS_OK;
    if_address  new_address = m_if_address;
    new_address.sub_net_mask = value;
    return change_if_address(new_address);
  }
  virtual ess_error_t set_dns_ip4(const ess_ip4address value)  {
    if(m_if_address.dns_address4 == value ) return ESS_OK;
    if_address  new_address = m_if_address;
    new_address.dns_address4 = value;
    return change_if_address(new_address);
  }
//-------set_ip6------------------------------------
  virtual ess_error_t set_local_ip6(const ess_ip6address value) {
    if(m_if_address.local_address6 == value ) return ESS_OK;
    if_address  new_address = m_if_address;
    new_address.local_address6 = value;
    return change_if_address(new_address);
  }
  virtual ess_error_t set_dns_ip6(const ess_ip6address value) {
    if(m_if_address.dns_address6 == value ) return ESS_OK;
    if_address  new_address = m_if_address;
    new_address.dns_address6 = value;
    return change_if_address(new_address);
  }
protected:
  virtual void on_start_up() { m_fStatus = ESS_NET_DEVICE_STATUS_DOWN; }
protected:
  ess_net_device_type m_tType;
  ess_net_device_status m_fStatus;
  if_address m_if_address;
};

#endif
