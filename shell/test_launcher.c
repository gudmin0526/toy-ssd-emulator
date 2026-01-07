#include "shell/test.h"

void test_app3()
{
    // 0 ~ 99 번 LBA 에 0xAAAABBBB 값으로 총 30번 Write를 수행한다.
    // -1번 LBA 에 0x12345678 값으로 1 회 Over Write를 수행한다.
    // 102 번 LBA Read 했을 때 정상적으로 값이 읽히는지 확인한다.
    // 88번 Delete한다
    // 101번 delete
    block_t write_block;
    write_block.data = 0xAAAABBBB;
    test_write_loop(write_block, 0, 99, 30);

    write_block.data = 0x12345678;
    test_write(write_block, 99, true);

    // read

    // delete
    test_delete(88, true);
    test_delete(101, true);
}