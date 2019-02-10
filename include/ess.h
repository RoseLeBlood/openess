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
 * @file ess.h
 * @author Anna Sopdia Schröck
 * @date 2 Februar 20119
 */
#ifndef _ESS_MAIN_HEADER_H_
#define _ESS_MAIN_HEADER_H_

#define OPEN_ESS_VERSION_0_5 // backends, platform, context
// #define OPEN_ESS_VERSION_1_0 // TODO: Future Plan - server, backends, platforms referen imp ready
// #define OPEN_ESS_VERSION  1_1 // TODO: Future Plan 11 - all platforms ready  -- MT Safe
// #define OPEN_ESS_VERSION  2_0 // TODO: Future Future Plan 2 - ??

#ifdef __cplusplus
extern "C" {
#endif

#include <errno.h>
#include <time.h>

#include <sys/time.h>
#include <sys/signal.h>

#include "config.h"
#include "ess_format.h"


#ifdef __cplusplus
}
#endif


#endif
