
#include "controller.h"

int is_valid_lba(char *str)
{ // LBA 유효성 검사 함수
    if (str == NULL)
        return 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]))
            return 0;
    }
    int lba = atoi(str);
    return (lba >= 0 && lba <= 99);
}

int is_valid_value(char *str)
{
    if (str == NULL)
        return 0;
    if (strncmp(str, "0x", 2) != 0)
        return 0; // 0x로 시작하는지, 10자리(0x포함)인지 확인

    if (strlen(str) != 10)
        return 0; // 길이가 10인지 확인

    for (int i = 2; i < 10; i++)
    { // 16진수 문자 검사
        char c = toupper(str[i]);
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F')))
            return 0;
    }
    return 1;
}

void execute_ssd(char *args)
{
    char cmd[200];
    sprintf(cmd, "ssd %s", args);
    system(cmd);
}

//---------- 명령 처리(임시) -------------

void do_read(char *lba)
{
    if (!is_valid_lba(lba))
    {
        printf("INVALID COMMAND\n");
        return;
    }

    char args[50];
    sprintf(args, "R %s", lba);
    execute_ssd(args);

    // ssd가 result.txt에 쓴 걸 읽어와서 출력
    FILE *fp = fopen("result.txt", "r");
    if (fp != NULL)
    {
        char buffer[100];
        if (fgets(buffer, sizeof(buffer), fp) != NULL)
        {
            printf("%s", buffer);
        }
        printf("\n");
        fclose(fp);
    }
}

void do_write(char *lba, char *val)
{
    if (!is_valid_lba(lba) || !is_valid_value(val))
    {
        printf("INVALID COMMAND\n");
        return;
    }
    char args[100];
    sprintf(args, "W %s %s", lba, val);
    execute_ssd(args);
}

void do_delete(char *lba)
{
    if (!is_valid_lba(lba))
    {
        printf("INVALID COMMAND\n");
        return;
    }

    char args[100];
    sprintf(args, "W %s 0x00000000", lba);

    execute_ssd(args);
}

void run_testapp1()
{
    printf("--- TestApp2 Start ---\n");

    for (int loop = 0; loop < 30; loop++)
    {
        for (int i = 0; i <= 5; i++)
        { // LBA 0 ~ 5
            char lba[10];
            sprintf(lba, "%d", i);
            do_write(lba, "0xAAAABBBB");
        }
    }

    for (int i = 0; i <= 5; i++)
    {
        char lba[10];
        sprintf(lba, "%d", i);
        do_write(lba, "0x12345678");
    }

    for (int i = 0; i <= 5; i++)
    {
        char lba[10];
        sprintf(lba, "%d", i);
    }
    printf("--- TestApp2 Pass ---\n");
}

void run_testapp2()
{
    printf("--- TestApp2 Start ---\n");

    for (int loop = 0; loop < 30; loop++)
    {
        for (int i = 0; i <= 5; i++)
        { // LBA 0 ~ 5
            char lba[10];
            sprintf(lba, "%d", i);
            do_write(lba, "0xAAAABBBB");
        }
    }

    for (int i = 0; i <= 5; i++)
    {
        char lba[10];
        sprintf(lba, "%d", i);
        do_write(lba, "0x12345678");
    }

    for (int i = 0; i <= 5; i++)
    {
        char lba[10];
        sprintf(lba, "%d", i);
    }
    printf("--- TestApp2 Pass ---\n");
}
