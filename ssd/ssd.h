#ifndef __SSD_H__
#define __SSD_H__

#define MAX_SIZE 100
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

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

typedef enum ret {
	SSD_OK = 0,
	WRITE_FAIL = 1,
	WRITE_OUT_OF_INDEX = 2,
	DELETE_FAIL_NOT_IN_USED = 3,
	DELETE_FAIL_CLEAR_FAILED = 4,
    READ_FAIL = 5,
    READ_OUT_OF_INDEX = 6,
} ret_t;

typedef struct block {
	int32_t data;
} block_t;

// TBD: 컨트롤러 완성
typedef struct ssd_controller {
    block_t* ssd;            // 메모리 (실제 데이터) 
    uint32_t num_blocks;

    uint32_t* used;          // 메타데이터 (블록 사용 여부)
    uint32_t num_meta_blocks;

    uint8_t dirty;
    uint32_t write_count;

    const char* img_path;    // "ssd.txt" 이미지 파일 경로
} ssd_controller_t;

typedef struct ssd {
	bool used[NUM_META_BLOCK];
	block_t block[NUM_BLOCK];
} ssd_t;

/* SSD 초기화 */
ret_t init_ssd(void);

/* CRUD */
ret_t write_block(uint8_t addr, int32_t data);
ret_t read_block  (uint8_t addr, int32_t* out_data);
ret_t delete_block(uint8_t addr);

#endif