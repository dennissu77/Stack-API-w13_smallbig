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
    // tQueueNode *newptr = NULL;
    // int mem_location;

    // our_malloc ( .......... );
    
    // if (newptr == NULL)
    // {
    //     printf("    Enqueue False!!! \n");
    //     return 0;
    // }
    
    // return 1;

    tQueueNode *newptr = NULL;
    int mem_location;

    our_malloc(data_type, (void **)&newptr, &mem_location);

    if (newptr == NULL) {
        printf("    Enqueue Failed!!! \n");
        return 0;
    }

    newptr->id = id;
    newptr->score = score;
    newptr->location = mem_location;
    newptr->data_type = data_type;
    newptr->next = NULL;

    if (queue->rear == NULL) {
        newptr->prev = NULL;
        queue->front = newptr;
        queue->rear = newptr;
    } else {
        newptr->prev = queue->rear;
        queue->rear->next = newptr;
        queue->rear = newptr;
    }

    queue->count++;
    return 1;
}

void dequeue_node(tQueue *queue, tQueueNode *target, int data_type)
{
    if (queue == NULL || target == NULL) {
        return;
    }

    // 當移除唯一節點時
    if (queue->front == target && queue->rear == target) {
        queue->front = NULL;
        queue->rear = NULL;
    } else if (target == queue->front) {
        // 移除前節點
        queue->front = target->next;
        if (queue->front) {
            queue->front->prev = NULL;
        }
    } else if (target == queue->rear) {
        // 移除尾節點
        queue->rear = target->prev;
        if (queue->rear) {
            queue->rear->next = NULL;
        }
    } else {
        // 移除中間節點
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }

    queue->count--;

    // 使用 our_free 釋放節點內部記憶體
    our_free(data_type, target->location);

    // 釋放節點結構本身的記憶體
    //free(target);


    // queue->count--;
    // our_free(data_type, target->location);
}

tQueueNode *find_target_node(tQueue *queue, int id, int data_type)
{
    // int i;
    // tQueueNode *target = queue->front;

    // return NULL;


    tQueueNode *target = queue->front;

    while (target != NULL) {
        if (target->id == id && target->data_type == data_type) {
            return target;
        }
        target = target->next;
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