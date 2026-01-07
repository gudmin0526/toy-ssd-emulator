#include <stdint.h>
#include <stdbool.h>
#include "ssd/ssd.h"

bool test_write_loop(block_t block, uint8_t start_addr, uint8_t end_addr, int count);
bool test_write(block_t block, uint8_t addr, bool log);
bool test_delete(uint8_t addr);
