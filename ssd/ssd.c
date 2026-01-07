#include <stdio.h>
#include <stdint.h>
#include "ssd.h"

uint8_t used[5][4]; // 비트로 접근: row * 32 + col
block_t SSD[MAX_SIZE];

uint8_t write_block(uint8_t addr, int32_t data) {
    SSD[addr].data = data;
    printf("%d\n", SSD[addr].data);

    return 0;
}

void dump(void) {
    printf("---dump---\n");
    for (int i = 0; i < MAX_SIZE; ++i) {
        printf("%d: %d\n", i, SSD[i].data);
    }
}