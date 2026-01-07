#include "ssd.h"

static uint32_t used[NUM_META_BLOCK] = { 0,  };
static block_t SSD[NUM_BLOCK] = { 0,  };

/* write, delete 업데이트 발생 시 1 증가 */
static uint8_t dirty_count = 0;
static uint32_t log_seq = 0;

static void log_msg(const char* msg) {
#if LOG 1
    FILE *log_fp = fopen("ssd.log", "a");
    fprintf(log_fp, "[%lld] %s\n", log_seq, msg);
    fclose(log_fp);
#endif
}

uint8_t init_ssd(void) {

    /* 전역 변수 초기화 */
    memset(SSD, 0, sizeof(block_t) * NUM_BLOCK);
    memset(used, 0, sizeof(uint32_t) * NUM_META_BLOCK);
    dirty_count = 0;

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
    size_t n_read = fread(SSD, sizeof(block_t), NUM_BLOCK, ssd_fp);

    /* used 배열로 읽어온다. */
    for (size_t i = 0; i < NUM_META_BLOCK; i++) {
        used[i] = (uint32_t)SSD[i].data;
    }
    fclose(ssd_fp);

    sleep_ms(1000);

    return 0;
}

static uint8_t flush_ssd(void) {
    /* 기존에 존재하는 파일 오픈 */
    FILE *ssd_fp = fopen("ssd.txt", "rb+");

    if (ssd_fp == NULL) {
        /* 파일 없으면 실패 반환 */
        return 1;
    }
    fwrite(SSD, sizeof(block_t), NUM_BLOCK, ssd_fp);
    fclose(ssd_fp);

    return 0;
}

static uint8_t integrity_check(void) {

}

uint8_t delete_block(uint8_t addr) {
    
}


#include "ssd.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint32_t used[NUM_META_BLOCK] = { 0,  };
static block_t SSD[NUM_BLOCK] = { 0,  };

/* write, delete 업데이트 발생 시 1 증가 */
static uint8_t dirty_count = 0;
static uint32_t log_seq = 0;

static void log_msg(const char* msg) {
#if LOG 1
    FILE *log_fp = fopen("ssd.log", "a");
    fprintf(log_fp, "[%lld] %s\n", log_seq, msg);
    fclose(log_fp);
#endif
}

uint8_t init_ssd(void) {

    /* 전역 변수 초기화 */
    memset(SSD, 0, sizeof(block_t) * NUM_BLOCK);
    memset(used, 0, sizeof(uint32_t) * NUM_META_BLOCK);
    dirty_count = 0;

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
    size_t n_read = fread(SSD, sizeof(block_t), NUM_BLOCK, ssd_fp);

    /* used 배열로 읽어온다. */
    for (size_t i = 0; i < NUM_META_BLOCK; i++) {
        used[i] = (uint32_t)SSD[i].data;
    }
    fclose(ssd_fp);

    sleep_ms(1000);

    return 0;
}

static uint8_t flush_ssd(void) {
    /* 기존에 존재하는 파일 오픈 */
    FILE *ssd_fp = fopen("ssd.txt", "rb+");

    if (ssd_fp == NULL) {
        /* 파일 없으면 실패 반환 */
        return 1;
    }
    fwrite(SSD, sizeof(block_t), NUM_BLOCK, ssd_fp);
    fclose(ssd_fp);

    return 0;
}

static uint8_t integrity_check(void) {

}

uint8_t delete_block(uint8_t addr) {
    
}

#ifndef SSD_H
#define SSD_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SSD_SIZE 100

typedef struct block {
	int32_t data;
} block_t;

uint8_t write_block(uint8_t addr, int32_t data);
uint8_t read_block(uint8_t addr, int32_t* out_data);
uint8_t delete_block(uint8_t addr);

#endif

uint8_t read_block(uint8_t addr, int32_t* out_data) {
    // 유효성 검사
    if (addr >= SSD_SIZE) {
        return 1; // Error: return 1 
    }
    // SSD 메모리 배열 초기화 
    int32_t virtual_nand[SSD_SIZE];

    for (int i = 0; i < SSD_SIZE; i++) {
        virtual_nand[i].data = 0; // 초기값 설정
    }

    // nand.txt 파일을 읽어 배열에 저장
    FILE* fp_nand = fopen("nand.txt", "r");
    if (fp_nand != NULL) {
        char line[12];
        int idx = 0;
        while (fgets(line, sizeof(line), fp_nand) && idx < SSD_SIZE) {
            virtual_nand[idx].data = (int32_t)strtoul(line, NULL, 16);  // 16진수 숫자로 변환
            idx++;
        }
        fclose(fp_nand);
    }
    // 데이터를 출력 파라미터에 저장
    *out_data = virtual_nand[addr].data;

    //result.txt에 기록 (덮어 씌우는 방식)
    FILE* fp_res = fopen("result.txt", "w");
    if (fp_res != NULL) {
        fprintf(fp_res, "0x%08X\n", *out_data); 
        fclose(fp_res);
    }

    

    return 0;
}



