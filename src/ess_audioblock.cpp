#include "ess_audioblock.h"

uint32_t m_memory_pool_available_mask[NUM_MASKS];
uint16_t m_memory_pool_first_mask;
uint16_t m_memory_used;
uint16_t m_memory_used_max;
uint16_t m_memory_size;

ess_audioblock_t * m_pMemory_pool;

#if ESS_MEMORY_MAP_EXTERN != ESS_ON
ess_audioblock_t _memory_map_data[ESS_USED_AUDIO_BLOCKS];
#endif

ess_error_t __memory_map_internal_create(unsigned int num, ess_audioblock_t* _static_data) {
	unsigned int i;

	if (num > ( ESS_MAX_AUDIO_MEMORY / ESS_DEFAULT_AUDIO_PACKET_SIZE / 2) )
		num =  ESS_MAX_AUDIO_MEMORY / ESS_DEFAULT_AUDIO_PACKET_SIZE / 2;

	m_memory_size = num;
	m_pMemory_pool = _static_data;
	m_memory_pool_first_mask = 0;

	for (i=0; i < NUM_MASKS; i++) {
		if(i < num) {
			m_memory_pool_available_mask[i >> 5] |= (1 << (i & 0x1F));
			_static_data[i].memory_pool_index = i;
		}
		else
			m_memory_pool_available_mask[i] = 0;
	}
	printf("[MEM] Init on %x with %d\n", (int)_static_data, num);
	return ESS_OK;
}



#if ESS_MEMORY_MAP_EXTERN == ESS_ON
ess_error_t ess_audioblock_create(unsigned int num, ess_audioblock_t* _static_data) {
	return __memory_map_internal_create(num, _static_data);
}
#else
ess_error_t ess_audioblock_create() {
	return __memory_map_internal_create(ESS_USED_AUDIO_BLOCKS, _memory_map_data);
}
#endif


ess_audioblock_t * ess_audioblock_alloc(void) {
	uint32_t n, index, avail;
	uint32_t *p, *end;
	ess_audioblock_t *block;
	uint32_t used;

	p = m_memory_pool_available_mask;
	end = p + NUM_MASKS;

	index = m_memory_pool_first_mask;
	p += index;
	while (1) {
		if (p >= end) { return NULL; }
		avail = *p;
		if (avail) break;
		index++;
		p++;
	}
	n = __builtin_clz(avail);
	avail &= ~(0x80000000 >> n);
	*p = avail;
	if (!avail) index++;

	m_memory_pool_first_mask = index;
	used = m_memory_used + 1;
	m_memory_used = used;

	index = p - m_memory_pool_available_mask;
	block = m_pMemory_pool + ((index << 5) + (31 - n));
	block->ref_count = 1;
	if (used > m_memory_used_max) m_memory_used_max = used;

	block->format = ESS_DEFAULT_SERVER_FORMAT;

	#if ESS_MEMORY_MAP_DEBUG == 1
		printf("[0x%x:%d]  ess_audioblock_alloc: %d\n", (uint32_t)block, block->memory_pool_index,  block->ref_count);
	#endif

	return block;
}
uint32_t  ess_audioblock_relese(ess_audioblock_t * block) {
	uint32_t mask = (0x80000000 >> (31 - (block->memory_pool_index & 0x1F)));
	uint32_t index = block->memory_pool_index >> 5;

  if (block->ref_count > 1) {
		block->ref_count--;
		#if ESS_MEMORY_MAP_DEBUG == 1
			printf("[0x%x:%d]  ess_audioblock_relese: %d\n", (uint32_t)block, block->memory_pool_index,  block->ref_count);
		#endif
	} else {
		#if ESS_MEMORY_MAP_DEBUG == 1
		uint16_t old_pool_index = block->memory_pool_index;
		#endif
		m_memory_pool_available_mask[index] |= mask;
		if (index < m_memory_pool_first_mask) m_memory_pool_first_mask = index;
		m_memory_used--;

		#if ESS_MEMORY_MAP_DEBUG == 1
			printf("[0x%x:%d]  ess_audioblock_free\n", (uint32_t)block, old_pool_index);
		#endif
	}
	return block->ref_count;
}
ess_audioblock_t* ess_audioblock_take(ess_audioblock_t* block) {
	if(block) { block->ref_count++; }
	#if ESS_MEMORY_MAP_DEBUG == 1
		printf("[0x%x:%d]  ess_audioblock_take: %d\n", (uint32_t)block, block->memory_pool_index,  block->ref_count);
	#endif
	return block;
}

uint16_t ess_audioblock_used() { return m_memory_used; }
uint16_t ess_audioblock_max_used() { return m_memory_used_max; }
uint16_t ess_audioblock_num() { return m_memory_size; }

void ess_audioblock_set_null(ess_audioblock_t * block ) {
	ess_audioblock_set(block, 0);
}
void ess_audioblock_set(ess_audioblock_t * block, uint32_t value) {
	ess_memset(block->data, value, ESS_DEFAULT_AUDIO_PACKET_SIZE);
}
