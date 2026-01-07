#ifndef __SSD_H__
#define __SSD_H__

#define MAX_SIZE 100
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

/* SSD 초기화 */
uint8_t init_ssd(void);

/* CRUD */
uint8_t write_block (uint8_t addr, int32_t data);
uint8_t read_block  (uint8_t addr, int32_t* out_data);
uint8_t delete_block(uint8_t addr);

void dump(void);
static uint8_t flush_ssd(void);
static uint8_t integrity_check(void);
uint8_t delete_block(uint8_t addr);

#endif