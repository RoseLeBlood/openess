#include "ess.h"

void ess_audioblock_set_null(ess_audioblock_t * block ) {
	ess_memset(block->data, 0, ESS_DEFAULT_AUDIO_PACKET_SIZE);
}
void ess_audioblock_set(ess_audioblock_t * block, uint32_t value) {
	ess_memset(block->data, value, ESS_DEFAULT_AUDIO_PACKET_SIZE);
}
