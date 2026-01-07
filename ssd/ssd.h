#ifndef SSD_H
#define SSD_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* UNIX, WINDOWS 크로스 플랫폼 이식성 유지 */
#ifdef _WIN32
#include <windows.h>
#define sleep_ms(ms) Sleep(ms)
#else
#include <unistd.h>
#define sleep_ms(ms) usleep((ms) * 1000)
#endif

#define LOG 1

#define DIRTY_THRESHOLD 5
#define NUM_BLOCK 100
#define NUM_META_BLOCK 4
#define NUM_DATA_BLOCK 96

typedef struct block {
	int32_t data;
} block_t;

// TBD: 컨트롤러 완성
typedef struct ssd_controller {
    block_t* ssd;          // 메모리 (실제 데이터) 
    uint32_t num_blocks;

    uint32_t* used;        // 메타데이터 (블록 사용 여부)
    uint32_t num_meta_blocks;

    uint32_t write_count;

    const char* img_path; // "ssd.txt" 이미지 파일 경로
} ssd_controller_t;

/* SSD 초기화 */
uint8_t init_ssd(void);

/* CRUD */
uint8_t write_block (uint8_t addr, int32_t data);
uint8_t read_block  (uint8_t addr, int32_t* out_data);
uint8_t delete_block(uint8_t addr);

#endif