#include <stdlib.h>
#include "token.h"

void TokenArrayFree(TokenArray *tokArray)
{
    if (tokArray->Tokens)
    {
        for (int i = 0; i < tokArray->Size; i++)
        {
            Token current = tokArray->Tokens[i];
            if (current.Type == TOKEN_KEYWORD)
            {
                
            }
            else if (current.Type == TOKEN_IDENTIFIER)
            {
                free(current.TokenData.String);
            }
        }
        
        free(tokArray->Tokens);
        tokArray->Tokens = 0;
    }
    
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
