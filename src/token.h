#ifndef TOKEN_H
#define TOKEN_H

#include "types.h"

typedef enum
{
    TOKEN_UNDEFINED = 0,

    // TODO: Put all single character tokens in ASCII table order here.
    TOKEN_NOT = '!',
    TOKEN_DOUBLE_QUOTE = '"',
    TOKEN_HASH = '#',
    TOKEN_MODULO = '%',
    TOKEN_BITWISE_AND = '&',
    TOKEN_SINGLE_QUOTE = '\'',

    TOKEN_OPEN_PAREN = '(',
    TOKEN_CLOSE_PAREN = ')',

    TOKEN_MUL = '*',
    TOKEN_PLUS = '+',
    TOKEN_COMMA = ',',
    TOKEN_MINUS = '-',
    TOKEN_DOT = '.',
    TOKEN_FORWARD_SLASH = '/',

    TOKEN_COLON = ':',
    TOKEN_SEMICOLON = ';',
    TOKEN_LESS = '<',
    TOKEN_EQUAL = '=',
    TOKEN_BIGGER = '>',

    TOKEN_OPEN_SQUARE_BRACKET = '[',
    TOKEN_CLOSE_SQUARE_BRACKET = ']',

    TOKEN_XOR = '^',

    TOKEN_OPEN_BRACKET = '{',
    TOKEN_BITWISE_OR = '|',
    TOKEN_CLOSE_BRACKET = '}',

    TOKEN_BITWISE_NOT = '~',

    // TODO: Put all non single character tokens after this one
    TOKEN_UNUSED = 128,

    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,

    // TODO: Put literal token types here.
    TOKEN_INT_LITERAL,
    TOKEN_STRING_LITERAL,
    TOKEN_FLOAT_LITERAL,
    TOKEN_DOUBLE_LITERAL,

    TOKEN_END_OF_CONTENT,

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

void TokenArrayFree(TokenArray* tokArray);
void TokenArrayAdd(TokenArray* tokArray, Token token);
void TokenArrayTrimToSize(TokenArray* tokArray);

#endif