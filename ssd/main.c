#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "ssd.h"

int main(int argc, char* argv[]) {
    char op = argv[0][0];
    char _addr[128] = { 0, };
    char _value[128] = { 0, };

    strcpy(_addr, argv[1]); 
    uint8_t addr = (uint8_t)atoi(_addr);

    int32_t value = 0;

    switch (op) {
    case 'R':
        read_block(addr, &value);
        return value;
    case 'W':
        value = (int32_t)atoi(_value);
        write_block(addr, value);
    case 'D':
        delete_block(addr);
    case 'FR':
        fullread_block();
    default:
        break;
    }

    return 0;
}