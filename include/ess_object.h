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
 * @file ess_object.h
 * @author Anna Sopdia Schröck
 * @date 09 März 2019
 * @brief ESS basic class all ess objects
 *
 *
 */
 /**
 * @addtogroup ess
 * @{
 */
#ifndef __ESS_OBJECT_H__
#define __ESS_OBJECT_H__

#include <sstream>

class ess_object {
  friend std::ostream& operator>>(std::ostream& stream, ess_object& obj); // to_string
  friend std::istream& operator<< (std::istream& stream, ess_object& obj); // from_string

public:
  ess_object() : m_strName("ess_object") { }
  ess_object(std::string name) : m_strName(name) {  }

  std::string get_name() { return m_strName; }
  void set_name(const std::string name) { m_strName = name; }

  virtual std::string to_string() { return m_strName; }
  virtual void from_string(const std::string str) { m_strName = str; }
private:
  std::string m_strName;
};

#endif
/**
* @}
*/
