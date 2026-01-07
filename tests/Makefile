CC := gcc
CFLAGS := -O2 -Wall -Wextra -Werror -I../ssd -I../include -I../

BIN_DIR := ../bin
UNIT_BIN := $(BIN_DIR)/regression_tests

# ssd 폴더의 .c들을 전부 링크 (너희 실제 파일명 구조에 맞게 동작)
SSD_SRC := ../ssd/ssd.c
UNIT_SRC := $(wildcard unit/*.c)

.PHONY: unit clean

unit:
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(UNIT_BIN) $(SSD_SRC) $(UNIT_SRC)
	./$(UNIT_BIN)

clean:
	rm -f $(UNIT_BIN)
