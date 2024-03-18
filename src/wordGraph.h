#ifndef WORDGRAPH_H
#define WORDGRAPH_H

#include "types.h"

typedef enum
{
    STRNODETYPE_NONE,
    STRNODETYPE_END,
} StringNodeType;

typedef struct StringNode
{
    char Key;
    StringNodeType Type;
    struct StringNode* Next;
} StringNode;

typedef struct StringNodeQueue
{
    StringNode** Nodes;
    u64 Size;
    u64 Capacity;
} StringNodeQueue;

typedef struct Word
{
    StringNode* Start;
    StringNode* End;
    u64 Size;
} Word;

typedef struct WordGraph
{
    Word* Words;
    StringNode* End;
    u64 Size;
    u64 Capacity;
} WordGraph;

void StringNodeQueueFree(StringNodeQueue* queue);
void StringNodeQueueTrimToSize(StringNodeQueue* queue);
void StringNodeQueuePush(StringNodeQueue* queue, StringNode* node);
StringNode* StringNodeQueuePop(StringNodeQueue* queue);
Word WordFromString(const char* string);
void WordGraphFree(WordGraph* graph);
void WordGraphAddWord(WordGraph* graph, Word word);
void WordGraphTrimToSize(WordGraph* graph);

#endif