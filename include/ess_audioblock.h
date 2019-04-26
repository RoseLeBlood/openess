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
 * @file ess_audioblock.h
 * @author Anna Sopdia Schröck
 * @date 18 April 2019
 * @brief OpenESS audio memory map - allocater for `ess_audioblock_t`
 *
 */
#ifndef _OPENESS_AUDIO_MEMORY_MAP_
#define _OPENESS_AUDIO_MEMORY_MAP_

typedef struct ess_audioblock {
  uint8_t  ref_count;
  uint16_t memory_pool_index;
  float    data[ESS_DEFAULT_AUDIO_PACKET_SIZE];
  ess_format_t format;
} ess_audioblock_t;


#if ESS_MEMORY_MAP_EXTERN == ESS_ON
ess_error_t ess_audioblock_create(unsigned int num, ess_audioblock_t* _static_data);
#else
ess_error_t ess_audioblock_create();
#endif

ess_audioblock_t *ess_audioblock_alloc(void);
uint32_t ess_audioblock_relese(ess_audioblock_t * block);
ess_audioblock_t* ess_audioblock_take(ess_audioblock_t * block);


uint16_t ess_audioblock_used();
uint16_t ess_audioblock_max_used();
uint16_t ess_audioblock_num();


void ess_audioblock_set_null(ess_audioblock_t * block );
void ess_audioblock_set(ess_audioblock_t * block, uint32_t value);


#endif
