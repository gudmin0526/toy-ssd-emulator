#ifndef SSD_H
#define SSD_H

#include <stdint.h>

#define MAX_SIZE 100

typedef struct block {
	int32_t data;
} block_t;

#endif