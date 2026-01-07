#include <assert.h>
#include "ssd.h"

// 동작(behaviour) 기반 유닛 테스트
void test_write_sets_used_bit(void) {
	init_ssd();
	
    int addr = 7;
    int data = 0x12345678;
	write_block(addr, data);
	
	int q = addr / 32;
	int r = addr % 32;
	
	uint32_t mask = (uint32_t)0x1 << r;

    ssd_t* p_SSD = get_ssd();
	assert((p_SSD->block[q].data & mask) == mask);
	assert((p_SSD->block[q].data & ~((uint32_t)0x1 << r)) == 0);
	assert(p_SSD->block[addr].data == data);
}

// 계약(contract) 기반 명세 테스트
void test_write_overwrite_data(void) {
	init_ssd();
	
    int addr = 7;
    int data = 0xABCDE123;

	write_block(addr, data);
	write_block(addr, data);

	ssd_t* p_SSD = get_ssd();
	assert(p_SSD->block[addr].data == data);
	// assert(write_block(3, 100) == ERR_ALREADY_USED); overwrite가 에러인 경우
}