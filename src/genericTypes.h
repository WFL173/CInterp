#ifndef GENERICTYPES_H
#define GENERICTYPES_H

#include "types.h"

typedef struct Queue
{
    int* Values;
    u64 Size;
    u64 Capacity;
} Queue;

int StringLength(const char* string);
Queue QueueInit(u64 capacity);
void QueueFree(Queue* queue);
void QueueTrimToSize(Queue* queue);
void QueuePush(Queue* queue, int element);
int QueuePop(Queue* queue);

#endif