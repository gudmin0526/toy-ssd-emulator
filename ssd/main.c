#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "ssd.h"

int main(int argc, char* argv[]) {
    init_ssd();
    
    char op = argv[1][0];
    uint8_t addr = (uint8_t)atoi(argv[2]);
    
    int32_t value = 0;

    switch (op) {
    case 'R':
        read_block(addr, &value);
        return value;
    case 'W':
        value = (int32_t)atoi(argv[3]);
        return write_block(addr, value);
    case 'D':
        return delete_block(addr);
    default:
        break;
    }

    return 0;
}