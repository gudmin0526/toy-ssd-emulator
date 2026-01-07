
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "controller.h"

#define MAX_CMD_SIZE 100

int main()
{
    char input[MAX_CMD_SIZE];

    while (1)
    {
        printf(">> ");
        if (fgets(input, MAX_CMD_SIZE, stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = 0; // 개행 문자 제거

        // 명령어 파싱
        char *cmd = strtok(input, " ");

        if (cmd == NULL)
            continue;

        if (strcmp(cmd, "ssd") == 0)
        {
            char *mode = strtok(NULL, " ");
            if (mode == NULL)
            {
                printf("INVALID COMMAND\n");
                continue;
            }
            if (strcmp(mode, "W") == 0)
            {
                char *lba = strtok(NULL, " ");
                char *val = strtok(NULL, " ");
                do_write(lba, val);
            }
            else if (strcmp(mode, "R") == 0)
            {
                char *lba = strtok(NULL, " ");
                do_read(lba);
            }
            else
            {
                printf("INVALID COMMAND\n");
            }
        }
        else if (strcmp(cmd, "delete") == 0)
        {
            char *lba = strtok(NULL, " ");
            do_delete(lba);
        }
        else if (strcmp(cmd, "testapp1") == 0)
        {
            run_testapp1();
        }
        else if (strcmp(cmd, "testapp2") == 0)
        {
            run_testapp2();
        }
        else if(strcmp(cmd, "exit") == 0)
        {
            break;
        }
        else
        {
            printf("INVALID COMMAND\n");
        }
    }
    return 0;
}