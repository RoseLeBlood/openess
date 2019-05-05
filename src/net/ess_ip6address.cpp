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
#include "net/ess_ip6address.h"
#include <sstream>

ess_ip6address::ess_ip6address()
  : ess_ipaddress(ESS_SOCKET_FAMILY_IP6, "ess_ip6address") {
    m_numbers[0] = 0;
    m_numbers[1] = 0;
    m_numbers[2] = 0;
    m_numbers[3] = 0;
    m_numbers[4] = 0;
    m_numbers[5] = 0;
    m_numbers[6] = 0;
    m_numbers[7] = 0;
}
ess_ip6address::ess_ip6address(unsigned short address[16], long scopid)
  : ess_ip6address(address, scopid, "ess_ip6address") { }

ess_ip6address::ess_ip6address(unsigned short address[16], long scopid, std::string name)
    : ess_ipaddress(ESS_SOCKET_FAMILY_IP6, "ess_ip6address"), m_scopid(scopid) {

      m_numbers[0] = (unsigned short)(address[0] * 256 + address[1]);
      m_numbers[1] = (unsigned short)(address[2] * 256 + address[3]);
      m_numbers[2] = (unsigned short)(address[4] * 256 + address[5]);
      m_numbers[3] = (unsigned short)(address[6] * 256 + address[7]);
      m_numbers[4] = (unsigned short)(address[8] * 256 + address[9]);
      m_numbers[5] = (unsigned short)(address[10] * 256 + address[11]);
      m_numbers[6] = (unsigned short)(address[12] * 256 + address[13]);
      m_numbers[7] = (unsigned short)(address[14] * 256 + address[15]);

}
ess_ip6address::ess_ip6address(const ess_ip6address& value) : ess_ipaddress(value) {
  m_scopid = value.m_scopid;
  m_numbers[0] = value.m_numbers[0];
  m_numbers[1] = value.m_numbers[1];
  m_numbers[2] = value.m_numbers[2];
  m_numbers[3] = value.m_numbers[3];
  m_numbers[4] = value.m_numbers[4];
  m_numbers[5] = value.m_numbers[5];
  m_numbers[6] = value.m_numbers[6];
  m_numbers[7] = value.m_numbers[7];
}

ess_ip6address::ess_ip6address(ess_ip4address v)
  : ess_ipaddress(ESS_SOCKET_FAMILY_IP6)  {

  m_numbers[0] = m_numbers[1] = m_numbers[2] = m_numbers[3] = m_numbers[4] = 0;
  m_numbers[5] = 0xFFFF;
  m_numbers[6] = (unsigned short)(((v.get_address() & 0x0000FF00) >> 8) |
                             ((v.get_address() & 0x000000FF) << 8));
  m_numbers[7] = (unsigned short)(((v.get_address() & 0xFF000000) >> 24) |
                              ((v.get_address() & 0x00FF0000) >> 8));
  m_scopid = 0;
  m_strName = "ess_ip64";
}

void ess_ip6address::get_address(unsigned short b[16])  const {
  b[0] = (unsigned char)((m_numbers[0] >> 8) & 0xFF);
  b[1] = (unsigned char)((m_numbers[0]     ) & 0xFF);
  b[2] = (unsigned char)((m_numbers[1] >> 8) & 0xFF);
  b[3] = (unsigned char)((m_numbers[1]     ) & 0xFF);
  b[4] = (unsigned char)((m_numbers[2] >> 8) & 0xFF);
  b[5] = (unsigned char)((m_numbers[2]     ) & 0xFF);
  b[6] = (unsigned char)((m_numbers[3] >> 8) & 0xFF);
  b[7] = (unsigned char)((m_numbers[3]     ) & 0xFF);
  b[8] = (unsigned char)((m_numbers[4] >> 8) & 0xFF);
  b[9] = (unsigned char)((m_numbers[4]     ) & 0xFF);
  b[10] = (unsigned char)((m_numbers[5] >> 8) & 0xFF);
  b[11] = (unsigned char)((m_numbers[5]     ) & 0xFF);
  b[12] = (unsigned char)((m_numbers[6] >> 8) & 0xFF);
  b[13] = (unsigned char)((m_numbers[6]     ) & 0xFF);
  b[14] = (unsigned char)((m_numbers[7] >> 8) & 0xFF);
  b[15] = (unsigned char)((m_numbers[7]     ) & 0xFF);
}

ess_ip4address ess_ip6address::to_ip4()  {
  long address = ((((uint32_t)m_numbers[6] & 0x0000FF00u) >> 8) |
                           (((uint32_t)m_numbers[6] & 0x000000FFu) << 8)) |
                           (((((uint32_t)m_numbers[7] & 0x0000FF00u) >> 8) |
                           (((uint32_t)m_numbers[7] & 0x000000FFu) << 8)) << 16);

      return ess_ip4address(address, get_name() );
}
std::string ess_ip6address::to_string() {
  std::ostringstream ss;


  return ss.str();
}
ess_ip6address& ess_ip6address::operator = (const ess_ip6address& value) {
  m_scopid = value.m_scopid;
  m_numbers[0] = value.m_numbers[0];
  m_numbers[1] = value.m_numbers[1];
  m_numbers[2] = value.m_numbers[2];
  m_numbers[3] = value.m_numbers[3];
  m_numbers[4] = value.m_numbers[4];
  m_numbers[5] = value.m_numbers[5];
  m_numbers[6] = value.m_numbers[6];
  m_numbers[7] = value.m_numbers[7];

  return *this;
}
ess_ip6address& ess_ip6address::operator = (const ess_ip4address& value) {
  unsigned int ip4 =value.get_address();

  m_numbers[0] = m_numbers[1] = m_numbers[2] = m_numbers[3] = m_numbers[4] = 0;
  m_numbers[5] = 0xFFFF;
  m_numbers[6] = (unsigned short)(((ip4 & 0x0000FF00) >> 8) |
                             ((ip4 & 0x000000FF) << 8));
  m_numbers[7] = (unsigned short)(((ip4 & 0xFF000000) >> 24) |
                              ((ip4 & 0x00FF0000) >> 8));
  m_scopid = 0;
  m_strName = "ess_ip64"; return *this;
}
bool ess_ip6address::is_equels(const ess_ip6address& other) const {
  if(m_scopid != other.m_scopid) return false;
  if(m_numbers[0] != other.m_numbers[0]) return false;
  if(m_numbers[1] != other.m_numbers[1]) return false;
  if(m_numbers[2] != other.m_numbers[2]) return false;
  if(m_numbers[3] != other.m_numbers[3]) return false;
  if(m_numbers[4] != other.m_numbers[4]) return false;
  if(m_numbers[5] != other.m_numbers[5]) return false;
  if(m_numbers[6] != other.m_numbers[6]) return false;
  return (m_numbers[7] == other.m_numbers[7]);
}
