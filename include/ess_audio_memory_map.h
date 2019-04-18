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
 * @file ess_audio_memory_map.h
 * @author Anna Sopdia Schröck
 * @date 18 April 2019
 * @brief OpenESS audio memory map - allocater for `ess_audioblock_t`
 *
 */
#ifndef _OPENESS_AUDIO_MEMORY_MAP_
#define _OPENESS_AUDIO_MEMORY_MAP_

#include "ess.h"


uint16_t ess_mem_used();
uint16_t ess_mem_max();

ess_audioblock_t *ess_mem_alloc(void);
void ess_mem_free(ess_audioblock_t * block);


#endif
