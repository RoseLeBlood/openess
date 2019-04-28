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
 * @file ess_ip_end_point.h
 * @author Anna Sopdia Schröck
 * @date 28 April 2019
 */

 #ifndef _ESS_IP_ENDPOINT_H_
 #define _ESS_IP_ENDPOINT_H_

 #include "ess_end_point.h"

 class ess_ip_end_point : public ess_end_point {
 public:
   ess_ip_end_point();
   ess_ip_end_point(ess_socket_fam_t fam);
   ess_ip_end_point(ess_socket_fam_t fam, uint16_t port);
   ess_ip_end_point(ess_socket_fam_t fam, uint16_t port, std::string name);

  virtual uint16_t get_port() const { return m_iPort; }
  virtual void set_port(uint32_t port);

  virtual bool is_valid() const { return !m_bInValid; }
 protected:
   uint16_t m_iPort;
   bool m_bInValid;
 };

 #endif
