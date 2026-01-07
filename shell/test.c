#include <stdio.h>
#include <stdbool.h>
#include "ssd/ssd.h"

// 일단 수행하고 로그 출력하는 정도로만 구현
// 검증 로직도 넣으면 좋을 듯

bool test_write_loop(block_t block, uint8_t start_addr, uint8_t end_addr, int count)
{
    // 0~n번 LBA 에 특정 값으로 m번 Write를 수행한다.

    for (int i = 0; i < count; i++) // 0 ~ 99 번 LBA 에 0xAAAABBBB 값으로 총 30번 Write를 수행한다.
    {
        for (int j = start_addr; j <= end_addr; j++)
        {
            if (write_block(i, block.data) != 0)
            {
                printf("Write Failed: Addr %d, Data %d\n", j, block.data);
                return false;
            }
        }
    }

    // log 일단 대충하기
    printf("Write Success: Data \n");
    return true;
}

bool test_write(block_t block, uint8_t addr)
{
    if (write_block(addr, block.data) == 0)
    {
        printf("Write Success: Addr %d, Data %d\n", addr, block.data);
        return true;
    }
    else
    {
        printf("Write Failed: Addr %d, Data %d\n", addr, block.data);
        return false;
    }
}

bool test_delete(uint8_t addr)
{
    if (delete_block(addr) == 0)
    {
        printf("Delete Success: Addr %d, Data %d\n", addr);
        return true;
    }
    else
    {
        printf("Delete Failed: Addr %d, Data %d\n", addr);
        return false;
    }
}
