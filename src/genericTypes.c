#include <stdlib.h>
#include "genericTypes.h"

int StringLength(const char* string)
{
    int result = 0;
    while (*string++)
    {
        result++;
    }
    return result;
}

Queue QueueInit(u64 capacity)
{
    Queue result = {0};
    result.Capacity = capacity;
    result.Values = malloc(capacity * sizeof(int));
    return result; 
}

void QueueFree(Queue *queue)
{
    if (queue->Values)
    {
        free(queue->Values);
        queue->Capacity = 0;
        queue->Size = 0;
    }
}

void QueueTrimToSize(Queue *queue)
{
    int* temp = malloc(queue->Size * sizeof(int*));
    for (int i = 0; i < queue->Size; i++)
    {
        temp[i] = queue->Values[i];
    }
    free(queue->Values);
    queue->Capacity = queue->Size;
    queue->Values = temp;
}

void QueuePush(Queue *queue, int element)
{

    if (queue->Size + 1 > queue->Capacity)
    {
        queue->Capacity = 2 * queue->Size + 1;
        int* temp = malloc(queue->Capacity * sizeof(int));
        for (int i = 0; i < queue->Size; i++)
        {
            temp[i] = queue->Values[i];
        }
        free(queue->Values);
        queue->Values = temp;
    }

    queue->Values[queue->Size] = element;
    queue->Size++;

}

int QueuePop(Queue *queue)
{
    int popResult = 0;

    if (queue->Size <= 0)
    {
        return popResult;
    }
    
    popResult = queue->Values[0];
    queue->Size--;

    for (int i = 1; i < queue->Size; i++)
    {
        queue->Values[i - 1] = queue->Values[i];
    }
    
    return popResult;
}
