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
 * @file ess_platform.h
 * @author Anna Sopdia Schröck
 * @date 3 Februar 20119
 * @brief all platform specific functions
 *
 */
#ifndef _ESS_PLATFORM_H_
#define _ESS_PLATFORM_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ESS_ENABLE_BACKEND_UDP
  ess_backend_facktory_t* ess_backend_udp_getFactory();
#endif
  ess_backend_facktory_t* ess_backend_null_getFactory();

#ifdef ESS_PLATFORM_ESP32
#include "platform/esp32/ess_platform_esp32.h"
#endif


#ifdef __cplusplus
}
#endif

#endif
