#include "space.h"

unsigned char buffer[ELEMENT_SIZE*NUM_BYTE_BUF];
unsigned char byte_buf_mask = 0;

//印出buffer的01佔用狀態
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
    int location;

    if (byte_buf_mask == FULL) {  // buffer 已滿
        return;
    }
    if (type == TYPE_SMALL) {// 如果是需要分類small的空間
        location = test_single_location(byte_buf_mask, NUM_BYTE_BUF);//找出small的空格並回傳位址  從mask的角度
        if (location >= 0) {//如果有回傳位址 不是回傳-1的話
            set_single_bit(&byte_buf_mask, location);//傳址呼叫byte_buf_mask
            *target = &buffer[location * ELEMENT_SIZE];//把在陣列中實際的記憶體位址的位置給到target 雙指標所以會影響函數外的結果
            *mem_location = location;//mem_location  是抽象化後的mask位址
        } else {
            return;
        }
    } else if (type == TYPE_LARGE) {// 如果是需要分類large的空間
        location = test_dual_location(byte_buf_mask, NUM_BYTE_BUF);//測試mask 要找到連續的兩個空位
        if (location >= 0) {
            set_dual_bit(&byte_buf_mask, location);
            *target = &buffer[location * ELEMENT_SIZE];
            *mem_location = location;
        } else {
            return;
        }
    }
}

//找出small空格  用查byte_buf_mask的方式
int test_single_location(unsigned char mask, int mask_length)
{
    //便歴byte_buf_mask 的mask直到找到(0)位址，也就是空位址
    for (int i = 0; i < mask_length; i++) {
        if (!(mask & (1 << i))) {
            return i;  // 找到可用位置 回傳移動的步數,等於回傳第幾個位址才是可用位址
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
