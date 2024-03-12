#ifndef LEXER_H
#define LEXER_H

#include "types.h"
#include "token.h"

typedef struct Lexer
{
    const u8* Contents;
    u64 ContentSize;
    u64 Cursor;
    u64 Line;
    u64 BeginningOfLine;
} Lexer;

Lexer LexerInit(const u8* contents, u64 contentSize);
Token LexerReadNextToken(Lexer* lexer);
TokenArray LexerTokenize(Lexer* lexer);

#endif