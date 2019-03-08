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

ess_platform_esp32::ess_platform_esp32() {

}
void ess_platform_esp32::create() {
  #ifdef ESS_ENABLE_BACKEND_OUT_I2S
  m_i2sController.setup(0);
  #endif
}
