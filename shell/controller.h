#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_valid_lba(char *str);
int is_valid_value(char *str);
void execute_ssd(char *args);
void do_read(char *lba);
void do_write(char *lba, char *val);
void do_delete(char *lba);
void run_testapp1();
void run_testapp2();