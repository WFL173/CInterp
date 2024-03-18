#include <stdlib.h>
#include "wordGraph.h"

int StringLength(const char* string)
{
    int result = 0;
    while (*string++)
    {
        result++;
    }
    return result;
}

void StringNodeQueueFree(StringNodeQueue* queue)
{
    if (queue->Nodes)
    {
        free(queue->Nodes);
        queue->Nodes = 0;
    }
}

void StringNodeQueueTrimToSize(StringNodeQueue* queue)
{
    StringNode** temp = malloc(queue->Size * sizeof(StringNode*));
    for (int i = 0; i < queue->Size; i++)
    {
        temp[i] = queue->Nodes[i];
    }
    free(queue->Nodes);
    queue->Capacity = queue->Size;
    queue->Nodes = temp;
}

void StringNodeQueuePush(StringNodeQueue* queue, StringNode* node)
{
    if (queue->Size + 1 > queue->Capacity)
    {
        queue->Capacity = 2 * queue->Size + 1;
        StringNode** temp = malloc(queue->Capacity * sizeof(StringNode*));
        for (int i = 0; i < queue->Size; i++)
        {
            temp[i] = queue->Nodes[i];
        }
        free(queue->Nodes);
        queue->Nodes = temp;
    }

    queue->Nodes[queue->Size] = node;
    queue->Size++;
}

StringNode* StringNodeQueuePop(StringNodeQueue* queue)
{
    StringNode* popResult = 0;

    if (queue->Size <= 0)
    {
        return popResult;
    }
    
    popResult = queue->Nodes[0];
    queue->Size--;

    for (int i = 1; i < queue->Size; i++)
    {
        queue->Nodes[i - 1] = queue->Nodes[i];
    }
    
    return popResult;
}

Word WordFromString(const char *string)
{
    Word result = {0};
    result.Size = StringLength(string);
    result.Start= malloc(result.Size * sizeof(StringNode));
    
    for (int i = 0; i < result.Size; i++)
    {
        result.Start[i].Key = string[i];
        result.Start[i].Type = STRNODETYPE_NONE;
        result.Start[i].Next = 0; 

        if (i + 1 < result.Size)
        {
            result.Start[i].Next = &result.Start[i + 1]; 
        }
        
    }

    result.End = &result.Start[result.Size - 1];

    return result;
}

void WordGraphFree(WordGraph *graph)
{
    for (int i = 0; i < graph->Size; i++)
    {
        Word currentWord = graph->Words[i];
        free(currentWord.Start);
    }
    
    if (graph->End)
    {
        free(graph->End);
        graph->End = 0;
    }
    
    if (graph->Words)
    {
        free(graph->Words);
        graph->Words = 0;
    }
    graph->Size = 0;
    graph->Capacity = 0;
}

void WordGraphAddWord(WordGraph* graph, Word word)
{
    if (!graph->End)
    {
        graph->End = malloc(sizeof(StringNode));
        graph->End->Next = 0;
        graph->End->Type = STRNODETYPE_END;
    }
    
    if (graph->Size + 1 > graph->Capacity)
    {
        graph->Capacity = 2 * graph->Size + 1;
        Word* temp = malloc(graph->Capacity * sizeof(Word));
        for (int i = 0; i < graph->Size; i++)
        {
            temp[i] = graph->Words[i];
        }
        free(graph->Words);
        graph->Words = temp;
    }

    word.End->Next = graph->End;
    graph->Words[graph->Size] = word;
    graph->Size++;
}

void WordGraphTrimToSize(WordGraph* graph)
{
    Word* temp = malloc(graph->Size * sizeof(Word));
    for (int i = 0; i < graph->Size; i++)
    {
        temp[i] = graph->Words[i];
    }
    free(graph->Words);
    graph->Capacity = graph->Size;
    graph->Words = temp;
}
