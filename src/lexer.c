#include <stdlib.h>
#include "lexer.h"
#include "log.h"
#include "lexerCharTypes.h"
#include "genericTypes.h"
#include "wordGraph.h"

const char* keywords[] =
{
    "return",
    "if",
    "for",
    "else",
    "while",
};

WordGraph keywordGraph = {0};

void KeywordGraphInit()
{
    if (keywordGraph.Words)
    {
        return;
    }

    for (int i = 0; i < ARRAY_COUNT(keywords); i++)
    {
        WordGraphAddWord(&keywordGraph, WordFromString(keywords[i]));
    }

}

void KeywordGraphFree()
{
    WordGraphFree(&keywordGraph);
}

int IsKeyword(const char* contents)
{
    int index = -1;

    StringNodeQueue currentStates = {0};
    StringNodeQueue nextStates = StringNodeQueueInit(keywordGraph.Size);
    StringNodeQueue temp = {0};
    Queue currentIndices = {0};
    Queue nextIndices = QueueInit(keywordGraph.Size);
    Queue tempIndices = {0};

    for (int i = 0; i < keywordGraph.Size; i++)
    {
        StringNodeQueuePush(&currentStates, keywordGraph.Words[i].Start);
        QueuePush(&currentIndices, i);
    }

    for (int i = 0; IsIdentifier(contents[i]); i++)
    {
        char currentChar = contents[i];
        
        nextStates.Size = 0;
        nextIndices.Size = 0;
        for (int j = 0; j < currentStates.Size; j++)
        {
            if (currentChar == currentStates.Nodes[j]->Key)
            {
                StringNodeQueuePush(&nextStates, currentStates.Nodes[j]->Next);
                QueuePush(&nextIndices, currentIndices.Values[j]);
            }   
        }

        temp = currentStates;
        currentStates = nextStates;
        nextStates = temp; 

        tempIndices = currentIndices;
        currentIndices = nextIndices;
        nextIndices = tempIndices; 

        if (currentStates.Size == 0)
        {
            break;
        }
          
    }
    
    for (int i = 0; i < currentStates.Size; i++)
    {
        if (currentStates.Nodes[i]->Type == STRNODETYPE_END)
        {
            index = QueuePop(&currentIndices);
            break;
        }
    }

    StringNodeQueueFree(&currentStates);
    StringNodeQueueFree(&nextStates);
    QueueFree(&currentIndices);
    QueueFree(&nextIndices);

    return index;
}

Lexer LexerInit(const u8* contents, u64 contentSize)
{
    Lexer result = {0};
    result.Contents = contents;
    result.ContentSize = contentSize;
    return result;
}

void LexerSkipSpaces(Lexer* lexer)
{
    while (lexer->Cursor < lexer->ContentSize && IsWhiteSpace(lexer->Contents[lexer->Cursor]))
    {
        char current = lexer->Contents[lexer->Cursor];
        lexer->Cursor++;
        if (current == '\n')
        {
            lexer->Line++;
            lexer->BeginningOfLine = lexer->Cursor;
        }
        
    }
    
}

Token LexerReadNextToken(Lexer* lexer)
{
    Token token = {0};
    int keywordIndex = -1;

    LexerSkipSpaces(lexer);

    if (lexer->Cursor >= lexer->ContentSize)
    {
        SC_INFO("end of content stream");
        token.Type = TOKEN_END_OF_CONTENT;
        return token;
    }
    
    // this switch will handle tokens composed of a single character.
    char current = lexer->Contents[lexer->Cursor];
    if (IsSingleCharToken(current))
    {
        SC_INFO("%c token found at line %lld, colon: %lld", current, lexer->Line, lexer->Cursor - lexer->BeginningOfLine);
        lexer->Cursor++;
        token.Type = current;
        return token;
    }
    
   if (IsDigit(current))
    {
        u64 currentCursorPosition = lexer->Cursor;
        s32 sum = 0;
        while (IsDigit(lexer->Contents[lexer->Cursor]))
        {
            sum *= 10;
            sum += lexer->Contents[lexer->Cursor] - '0';
            lexer->Cursor++;
        }
        
        SC_INFO("Integer literal %d found at line: %lld, colon: %lld", sum, lexer->Line, currentCursorPosition - lexer->BeginningOfLine);
        token.Type = TOKEN_INT_LITERAL;
        token.TokenData.IntValue = sum;
        return token;
    }

    if ((keywordIndex = IsKeyword(&lexer->Contents[lexer->Cursor])) != -1)
    {
        u64 currentCursorPosition = lexer->Cursor;
        lexer->Cursor += StringLength(keywords[keywordIndex]);
        
        SC_INFO("keyword %s found at line: %lld, colon: %lld", keywords[keywordIndex], lexer->Line, currentCursorPosition - lexer->BeginningOfLine);
        token.TokenData.IntValue = keywordIndex;
        token.Type = TOKEN_KEYWORD;
        return token;
    }

    if (IsIdentifierStart(current))
    {

        u64 currentCursorPosition = lexer->Cursor++;
        while (IsIdentifier(lexer->Contents[lexer->Cursor]))
        {
            lexer->Cursor++;
        }
        u64 identifierSize = lexer->Cursor - currentCursorPosition;
        u8* identifier = malloc(identifierSize + 1);

        for (int i = 0; i < identifierSize; i++)
        {
            identifier[i] = lexer->Contents[currentCursorPosition + i];
        }
        identifier[identifierSize] = '\0';

        SC_INFO("Identifier %s found at line: %lld, colon: %lld", identifier, lexer->Line, currentCursorPosition - lexer->BeginningOfLine);
        token.Type = TOKEN_IDENTIFIER;
        token.TokenData.String = identifier;

        return token;
    }
    
    lexer->Cursor++;
    return token;
}

TokenArray LexerTokenize(Lexer* lexer)
{
    TokenArray result = {0};
    KeywordGraphInit();

    while(lexer->Cursor < lexer->ContentSize)
    {
        Token token = LexerReadNextToken(lexer);
        TokenArrayAdd(&result, token);
    }

    KeywordGraphFree();
    TokenArrayTrimToSize(&result);
    return result;
}