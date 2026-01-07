#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "ssd.h"

// static uint32_t used[NUM_META_BLOCK] = { 0,  };
// static block_t SSD[NUM_BLOCK] = { 0,  };
static ssd_t SSD;

/* write, delete 업데이트 발생 시 1 증가 */
static uint32_t log_seq = 0;

ret_t write_block(uint8_t addr, int32_t data) {
    // SSD[addr].data = data;
    if ((addr < NUM_META_BLOCK) || (addr >= NUM_BLOCK)) {
        printf("write_block: write out of index!\n");
        return WRITE_OUT_OF_INDEX;
    }

    SSD.used[addr] = true;
    SSD.block[addr].data = data;
    ret_t result = flush_ssd();

    if (result != SSD_OK) {
        printf("write_block: write failed!\n");
        return WRITE_FAIL;
    }

    // printf("write_block: addr: %d, data: %d\n", addr, SSD[addr].data);
    printf("write_block: addr: %d, data: %d\n", addr, SSD.block[addr].data);
    return result;
}

static void log_msg(const char* msg) {
#if LOG
    FILE *log_fp = fopen("ssd.log", "a");
    fprintf(log_fp, "[%lld] %s\n", log_seq, msg);
    fclose(log_fp);
#endif
}

uint8_t init_ssd(void) {
    /* 전역 변수 초기화 */
    memset(SSD.block, 0, sizeof(block_t) * NUM_BLOCK);

    /* 파일 오픈 */
    FILE *ssd_fp = fopen("ssd.txt", "rb+");
    
    if (ssd_fp == NULL) {
        /* 파일이 없을 경우 새로 생성 */
        ssd_fp = fopen("ssd.txt", "wb+");
        if (ssd_fp == NULL) {
            /* 생성도 실패했으면 실패 반환 */
            return 1;
        }
    }

    /* 파일을 SSD 배열로 읽어온다 */
    size_t n_read = fread(SSD.block, sizeof(block_t), NUM_BLOCK, ssd_fp);

    // /* used 배열로 읽어온다. */
    // for (size_t i = 0; i < NUM_META_BLOCK; i++) {
    //     used[i] = (uint32_t)SSD.block[i].data;
    // }
    fclose(ssd_fp);

    sleep_ms(1000);

    return 0;
}

void dump(void) {
    printf("---dump---\n");
    for (int i = 0; i < MAX_SIZE; ++i) {
        printf("%d: %d\n", i, SSD.block[i].data);
    }
}

static ret_t flush_ssd(void) {
    /* 기존에 존재하는 파일 오픈 */
    FILE *ssd_fp = fopen("ssd.txt", "rb+");

    if (ssd_fp == NULL) {
        /* 파일 없으면 실패 반환 */
        return WRITE_FAIL;
    }
    fwrite(SSD.block, sizeof(block_t), NUM_BLOCK, ssd_fp);
    fclose(ssd_fp);

    return SSD_OK;
}

static uint8_t integrity_check(void) {

}

ret_t delete_block(uint8_t addr) {
    ret_t result = SSD.used[addr] ? SSD_OK : DELETE_FAIL_NOT_IN_USED;

    if (result != SSD_OK) {
        printf("delete_block: block not in used!\n");
        return DELETE_FAIL_NOT_IN_USED;
    }

    result = write_block(addr, 0);

    if (result != SSD_OK) {
        printf("delete_block: delete failed!\n");
        return DELETE_FAIL_CLEAR_FAILED;
    }

    SSD.used[addr] = false;

    return result;
}
