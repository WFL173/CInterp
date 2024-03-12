#include <stdlib.h>
#include "lexer.h"
#include "log.h"
#include "lexerCharTypes.h"

char* keywords[] =
{
    "return",
    "if",
    "for",
    "else",
    "while",
};

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

    LexerSkipSpaces(lexer);

    if (lexer->Cursor >= lexer->ContentSize)
    {
        SC_INFO("end of content stream");
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
    
    lexer->Cursor++;
    return token;
}

TokenArray LexerTokenize(Lexer* lexer)
{
    TokenArray result = TokenArrayInit();

    while(lexer->Cursor < lexer->ContentSize)
    {
        Token token = LexerReadNextToken(lexer);
        TokenArrayAdd(&result, token);
    }

    TokenArrayTrimToSize(&result);
    return result;
}