#include "queue.h"
#include "space.h"


tQueue* createQueue(void){    
    tQueue *queue;
    queue=(tQueue *) malloc (sizeof(tQueue));

    if (queue)
    {
        queue->front=NULL;
        queue->rear=NULL;  
        queue->count=0;
    }

    return queue;
}

int enqueue_node(tQueue *queue, int id, int score, int data_type)
{
    tQueueNode *newptr = NULL;
    int mem_location;

    our_malloc(data_type, (void **)&newptr, &mem_location);//獲取記憶體空間
    //執行完後newptr指標會指向一個新的空間   mem_location則表示這個空間的抽像位址（mask)

    //如果newptr爲NULL  代表our_malloc沒有賦予他空間位址，所以分配空間失敗。
    if (newptr == NULL) {
        printf("    Enqueue Failed!!! \n");
        return 0;
    }

    newptr->id = id;//記錄此節點儲存的值
    newptr->score = score;//目前沒有使用到
    newptr->location = mem_location;//記錄此結點的mask
    newptr->data_type = data_type;//small or large
    newptr->next = NULL;//queue插入點一定是在最後，所以插入點的後面沒有東西

    if (queue->rear == NULL) {//如果貯列爲空代表插入的是第一個節點
        newptr->prev = NULL;
        queue->front = newptr;
        queue->rear = newptr;
    } else {
        newptr->prev = queue->rear;//prev聯結之前的最後一個節點
        queue->rear->next = newptr;//更改前一個節點的rear指標
        queue->rear = newptr;//newptr設成最後一個節點
    }

    queue->count++;//county增加
    return 1;//代表新增節點成功
}

void dequeue_node(tQueue *queue, tQueueNode *target, int data_type)
{
    //target爲要刪除的結點的位址
    if (queue == NULL || target == NULL) {
        return;
    }

    // 當移除唯一節點時
    if (queue->front == target && queue->rear == target) {
        queue->front = NULL;
        queue->rear = NULL;
    } else if (target == queue->front) {//因爲要修改最前端的節點所以要 調整queue->front 
        // 移除前節點
        queue->front = target->next;
        if (queue->front) {
            queue->front->prev = NULL;
        }
    } else if (target == queue->rear) {//因爲要修改最"後端"的節點所以要 調整queue->rear 
        // 移除尾節點
        queue->rear = target->prev;
        if (queue->rear) {
            queue->rear->next = NULL;
        }
    } else {
        // 移除中間節點  移除既不是最前也不是最後 也不是唯一的結點
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }

    queue->count--;

    // 使用 our_free 釋放節點內部記憶體
    our_free(data_type, target->location);//用作清除對應的mask
    //因爲是模擬程式就是有一段預先宣告的空間，且只能使用那段空間，所以釋放記憶體只需要清除mask就好不需要去free()記憶體。

}

tQueueNode *find_target_node(tQueue *queue, int id, int data_type)
{
    tQueueNode *target = queue->front;

    while (target != NULL) {
        if (target->id == id && target->data_type == data_type) {//確認id跟要尋找的datatype都吻合
            return target;//回船要尋找的目標node的位址
        }
        target = target->next;//遍歷
    }

    return NULL;
}


void print_queue (tQueue *queue)
{
    int i;
    tQueueNode *target = queue->front;

    printf("      queue content: ");    
    for (i = 0; i < queue->count; i++)
    {
        printf ("%d(%d) ", target->id, target->data_type +1);
        target = target->next;
    }
    printf("\n");
}