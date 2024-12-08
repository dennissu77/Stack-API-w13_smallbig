#include <stdio.h>
#include <assert.h>
#include "../space.h" // 根據您的目錄結構，調整相對路徑


#define TYPE_SMALL              0
#define TYPE_LARGE              1

void test_function1() {
    // 假設 space.c 裡有一個 function1 函數
    // int result = function1(5);
    // assert(result == 25); // 替換為您預期的結果


    //test_single_location(unsigned char mask, int mask_length)
    print_buffer_status();

    int location = -1;
    unsigned char byte_buf_mask = 0;
    int i=test_single_location(byte_buf_mask,location);
    printf("i= %d\n",i);

    printf("test_function1 passed!\n");
}

void test_function2() {
    // 假設 space.c 裡有一個 function2 函數

    //char
    char *newptr = NULL;

    //our_malloc(TYPE_SMALL, void &newptr, int *mem_location)
    //assert(result == 7); // 替換為您預期的結果
    printf("test_function2 passed!\n");
}

int main() {
    test_function1();
    //test_function2();
    printf("All tests passed successfully.\n");
    return 0;
}
