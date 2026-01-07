#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "ssd.h"

static uint32_t used[4];
block_t SSD[MAX_SIZE];

uint8_t write_block(uint8_t addr, int32_t data) {
    SSD[addr].data = data;
    printf("write_block: addr: %d, data: %d\n", addr, SSD[addr].data);

    // 읽기
    FILE *fp = fopen("test.txt", "r+b");
    if (!fp) return 1;

    long offset = addr * (sizeof(int32_t) / sizeof(int8_t));
    fseek(fp, offset, SEEK_SET);

    fwrite(&data, sizeof(int32_t), 1, fp);
    fclose(fp);  

    return 0;
}

void dump(void) {
    printf("---dump---\n");
    for (int i = 0; i < MAX_SIZE; ++i) {
        printf("%d: %d\n", i, SSD[i].data);
    }
}