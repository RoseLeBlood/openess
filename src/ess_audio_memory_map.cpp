#include "ess_audio_memory_map.h"

#define NUM_MASKS  (((ESS_MAX_AUDIO_MEMORY / ESS_DEFAULT_AUDIO_PACKET_SIZE / 2) + 31) / 32)

ess_audioblock_t * _memory_pool;


uint32_t _memory_pool_available_mask[NUM_MASKS];
uint16_t _memory_pool_first_mask;
uint16_t _memory_used = 0;
uint16_t _memory_used_max = 0;

void ess_mem_init(unsigned int num, ess_audioblock_t* _static_data) {
	unsigned int i;
	unsigned int maxnum = ESS_MAX_AUDIO_MEMORY / ESS_DEFAULT_AUDIO_PACKET_SIZE / 2;

	if (num > maxnum)
		num = maxnum;

	_memory_pool = _static_data;
	_memory_pool_first_mask = 0;

	for (i=0; i < NUM_MASKS; i++) {
		_memory_pool_available_mask[i] = 0;
	}
	for (i=0; i < num; i++) {
		_memory_pool_available_mask[i >> 5] |= (1 << (i & 0x1F));
	}
	for (i=0; i < num; i++) {
		_static_data[i].memory_pool_index = i;
	}
	printf("[MEM] Init on %d with %d\n", (int)_static_data, num);
}

// Allocate 1 audio data block.  If successful
// the caller is the only owner of this new block
ess_audioblock_t * ess_mem_alloc(void) {
	uint32_t n, index, avail;
	uint32_t *p, *end;
	ess_audioblock_t *block;
	uint32_t used;

	p = _memory_pool_available_mask;
	end = p + NUM_MASKS;

	index = _memory_pool_first_mask;
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

	_memory_pool_first_mask = index;
	used = _memory_used + 1;
	_memory_used = used;

	index = p - _memory_pool_available_mask;
	block = _memory_pool + ((index << 5) + (31 - n));
	block->ref_count = 1;
	if (used > _memory_used_max) _memory_used_max = used;


	return block;
}




void ess_mem_free(ess_audioblock_t * block) {
  uint32_t mask = (0x80000000 >> (31 - (block->memory_pool_index & 0x1F)));
	uint32_t index = block->memory_pool_index >> 5;

  if (block->ref_count > 1) {
		block->ref_count--;
	} else {
		_memory_pool_available_mask[index] |= mask;
		if (index < _memory_pool_first_mask) _memory_pool_first_mask = index;
		_memory_used--;
	}
}

uint16_t ess_mem_used() {
    return _memory_used;
}
uint16_t ess_mem_max() {
  return _memory_used_max;
}
