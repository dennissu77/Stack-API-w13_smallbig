#include "space.h"

unsigned char buffer[ELEMENT_SIZE*NUM_BYTE_BUF];
unsigned char byte_buf_mask = 0;

void print_buffer_status (void)
{
    int i;
    unsigned char mask = 0x80;
  
    printf ("      byte_buf_mask: ");
    for (i = 0; i< NUM_BYTE_BUF; i++)
    {
        printf ("%d ", (byte_buf_mask & mask) >> (7-i));
        mask = mask >> 1;
    }

    printf ("\n");
}

void our_malloc(int type, void **target, int *mem_location)
{
    // int location;

    // if (byte_buf_mask == FULL){//代表buffer已滿 無法分配
    //     return;
    // }
    // else if (type == TYPE_SMALL)
    // {
    //     // location = test_single_location( ............ );//byte_buf_mask
    //     // set_single_bit(.............);
    //     // *target = .............. ;
    //     // *mem_location = location;
    // }
    // else
    // {

    //     // location = test_dual_location(............. );
    //     // if (location >= 0)
    //     // {
    //     //     set_dual_bit( .......... );


    //     // }
    //     // else
    //     // {
    //     //     return;
    //     // }
    // }    

        int location;

    if (byte_buf_mask == FULL) {  // buffer 已滿
        return;
    }
    if (type == TYPE_SMALL) {
        location = test_single_location(byte_buf_mask, NUM_BYTE_BUF);
        if (location >= 0) {
            set_single_bit(&byte_buf_mask, location);
            *target = &buffer[location * ELEMENT_SIZE];
            *mem_location = location;
        } else {
            return;
        }
    } else if (type == TYPE_LARGE) {
        location = test_dual_location(byte_buf_mask, NUM_BYTE_BUF);
        if (location >= 0) {
            set_dual_bit(&byte_buf_mask, location);
            *target = &buffer[location * ELEMENT_SIZE];
            *mem_location = location;
        } else {
            return;
        }
    }
}

//找出small空格
int test_single_location(unsigned char mask, int mask_length)
{
    
    //printf("TTT\n");
    for (int i = 0; i < mask_length; i++) {
        if (!(mask & (1 << i))) {
            return i;  // 找到可用位置
        }
    }
    return -1;  // 無可用位置


}

//設定記憶體使用狀態
void set_single_bit(unsigned char *mask, int location)
{
    *mask |= (1 << location);  // 設定對應位元為 1   location爲設定的位置
}

//找出big空格
int test_dual_location(unsigned char mask, int mask_length)
{
        for (int i = 0; i < mask_length - 1; i++) {
        if (!(mask & (1 << i)) && !(mask & (1 << (i + 1)))) {
            return i;  // 找到連續兩個空位
        }
    }
    return -1;  // 無連續空位

}

//設定big記憶體狀態
void set_dual_bit(unsigned char *mask, int location)
{
    *mask |= (1 << location) | (1 << (location + 1));  // 設定連續兩個位元為 1

}

void clear_single_bit(unsigned char *mask, int location)
{
    *mask &= ~(1 << location);  // 清除對應位元
}

void clear_dual_bit(unsigned char *mask, int location)
{
    *mask &= ~((1 << location) | (1 << (location + 1)));  // 清除連續兩個位元
}

void our_free(int type, int mem_location)
{
    if (type == TYPE_SMALL) {
        // 確保 mem_location 在有效範圍內
        if (mem_location < 0 || mem_location >= NUM_BYTE_BUF) {
            printf("Invalid memory location for TYPE_SMALL: %d\n", mem_location);
            return;
        }
        // 清除對應位元
        clear_single_bit(&byte_buf_mask, mem_location);
    } else if (type == TYPE_LARGE) {
        // 確保 mem_location 在有效範圍內
        if (mem_location < 0 || mem_location >= NUM_BYTE_BUF - 1) {
            printf("Invalid memory location for TYPE_LARGE: %d\n", mem_location);
            return;
        }
        // 清除連續兩個位元
        clear_dual_bit(&byte_buf_mask, mem_location);
    } else {
        printf("Invalid memory type: %d\n", type);
    }
}
