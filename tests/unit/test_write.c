#include "ssd.h"

// 동작(behaviour) 기반 유닛 테스트
void test_write_sets_used_bit(void) {
	init_ssd();
	
	write_block(3, 42);
	
	int q = 3 / 32;
	int r = 3 % 32;
	
	uint32_t mask = (uint32_t)1 << r;

    ssd_t* p_SSD = get_ssd();
	assert((p_SSD->block[q].data & mask) == mask);
	assert((p_SSD->block[q].data & ~((uint32_t)1 << r)) == 0);
	assert(p_SSD->block[3].data == 42);
}

// 계약(contract) 기반 명세 테스트
void test_write_overwrite_data(void) {
	init_ssd();
	
	write_block(3, 42);
	write_block(3, 100);
    
	ssd_t* p_SSD = get_ssd();
	assert(p_SSD->block[3].data == 100);
	// assert(write_block(3, 100) == ERR_ALREADY_USED); overwrite가 에러인 경우
}