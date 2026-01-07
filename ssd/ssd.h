#ifndef SSD_H
#define SSD_H

#include <stdint.h>

#define SSD_SIZE 100

typedef struct block {
	int32_t data;
} block_t;

uint8_t write_block (uint8_t addr, int32_t data);
uint8_t read_block  (uint8_t addr, int32_t* out_data);
uint8_t delete_block(uint8_t addr);

#endif