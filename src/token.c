#include <stdlib.h>
#include "token.h"

TokenArray TokenArrayInit()
{
    TokenArray result = {0};
    return result;
}

void TokenArrayAdd(TokenArray* tokArray, Token token)
{
    if (tokArray->Size + 1 > tokArray->Capacity)
    {
        tokArray->Capacity = 2 * tokArray->Size + 1;
        Token* temp = malloc(tokArray->Capacity * sizeof(Token));
        for (int i = 0; i < tokArray->Size; i++)
        {
            temp[i] = tokArray->Tokens[i];
        }
        free(tokArray->Tokens);
        tokArray->Tokens = temp;
    }

    tokArray->Tokens[tokArray->Size] = token;
    tokArray->Size++;
}

void TokenArrayTrimToSize(TokenArray* tokArray)
{
    Token* temp = malloc(tokArray->Size * sizeof(Token));
    for (int i = 0; i < tokArray->Size; i++)
    {
        temp[i] = tokArray->Tokens[i];
    }
    free(tokArray->Tokens);
    tokArray->Capacity = tokArray->Size;
    tokArray->Tokens = temp;

}
