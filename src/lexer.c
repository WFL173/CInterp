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
    
    if (lexer->Contents[lexer->Cursor] == ';')
    {
        SC_INFO("; found at line: %lld, colon: %lld", lexer->Line, lexer->Cursor - lexer->BeginningOfLine);
        lexer->Cursor++;
        return token;
    }

    if (IsIdentifierStart(lexer->Contents[lexer->Cursor]))
    {
        SC_INFO("Identifier found at line: %lld, colon: %lld", lexer->Line, lexer->Cursor - lexer->BeginningOfLine);
        lexer->Cursor++;
        while (IsIdentifier(lexer->Contents[lexer->Cursor]))
        {
            lexer->Cursor++;
        }
        
        return token;
    }

    if (IsDigit(lexer->Contents[lexer->Cursor]))
    {
        SC_INFO("Integer literal found at line: %lld, colon: %lld", lexer->Line, lexer->Cursor - lexer->BeginningOfLine);
        lexer->Cursor++;
        while (IsDigit(lexer->Contents[lexer->Cursor]))
        {
            lexer->Cursor++;
        }
        
        return token;
    }
    
    lexer->Cursor++;
    return token;
}

TokenArray LexerParse(Lexer* lexer)
{
    TokenArray result = {0};

    while(lexer->Cursor < lexer->ContentSize)
    {
        LexerReadNextToken(lexer);
    }

    return result;
}