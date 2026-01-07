#include <stdio.h>
#include <assert.h>

// 다른 파일에 정의된 테스트 함수들 선언
void test_write_sets_used_bit(void);
void test_write_overwrite_data(void);

int main(void) {
    test_write_sets_used_bit();
    test_write_overwrite_data();

    puts("[OK] regression unit tests passed");
    return 0;
}