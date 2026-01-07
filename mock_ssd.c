#include <stdio.h>
#include <string.h>

// 쉘이 명령을 잘 보냈나 확인만 하는 '연기자' 프로그램
int main(int argc, char *argv[]) {
    // argv[1]: W 또는 R

    if (argc < 2) return 0; // 아무것도 안 들어오면 종료

    // 1. 읽기(R) 명령이 들어오면?
    // 무조건 result.txt에 가짜 값을 적어준다.
    if (strcmp(argv[1], "R") == 0) {
        FILE *fp = fopen("result.txt", "w");
        if (fp != NULL) {
            // 테스트를 위해 그냥 고정된 값을 적어둠!
            fprintf(fp, "0x12345678"); 
            fclose(fp);
        }
    }
    
    // 2. 쓰기(W) 명령이 들어오면?
    // 아무것도 안 하고 그냥 성공한 척 조용히 종료한다.
    // (왜냐? 쉘은 쓰기 할 때 화면에 아무것도 안 띄우니까!)

    return 0;
}