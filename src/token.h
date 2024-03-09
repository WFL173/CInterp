#ifndef TOKEN_H
#define TOKEN_H

#include "types.h"

typedef enum
{
    TOKEN_UNDEFINED = 0,

    TOKEN_INT_LITERAL,
    TOKEN_STRING_LITERAL,

    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,

    TOKEN_SEMICOLON,

    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,

    TOKEN_OPEN_BRACKET,
    TOKEN_CLOSE_BRACKET,

    TOKEN_OPEN_SQUARE_BRACKET,
    TOKEN_CLOSE_SQUARE_BRACKET,

} TokenType;

typedef struct Token
{
    TokenType Type;

    union TokenData
    {
        s32 IntValue;
        u8* String;
    } TokenData;

} Token;

typedef struct TokenArray
{
    Token* Tokens;
    u64 Size;
    u64 Capacity;
} TokenArray;

TokenArray TokenArrayInit();
void TokenArrayAdd(TokenArray* tokArray, Token token);
void TokenArrayTrimToSize(TokenArray* tokArray);

#endif