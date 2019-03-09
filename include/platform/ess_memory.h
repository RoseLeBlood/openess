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
 * @file ess_memory.h
 * @author Anna Sopdia Schröck
 * @date 09 März 20119
 * @brief platform audio memory functions
 *
 *
 */
 #ifndef _ESS_PLATFORM_MEMORY_H_
 #define _ESS_PLATFORM_MEMORY_H_

 #include "ess.h"

void* ess_malloc(unsigned int size);
void* ess_malloc_audio(unsigned int size);

void* ess_calloc(size_t nmemb, size_t size);
void* ess_calloc_audio(size_t nmemb, size_t size);

void* ess_realloc(void *ptr, size_t size);
void* ess_realloc_audio(void *ptr, size_t size);

void ess_free(void* buffer);

void ess_zeromem(void* buffer, unsigned int size);
void ess_memset(void* buffer, int data, unsigned int size);

void ess_memcpy(void* dest, void* src, unsigned int size);

 #endif
