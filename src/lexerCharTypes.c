#include "lexerCharTypes.h"

int IsIdentifier(char key)
{
    return IsAlNum(key) || key == '_';
}

int IsIdentifierStart(char key)
{
    return IsAlpha(key) || key == '_';
}

int IsAlpha(char key)
{
    if ((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z'))
    {
        return 1;
    }

    return 0;
}

int IsAlNum(char key)
{
    if ((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z') || (key >= '0' && key <= '9'))
    {
        return 1;
    }

    return 0;
}

int IsDigit(char key)
{
    if (key >= '0' && key <= '9')
    {
        return 1;
    }

    return 0;
}

int IsWhiteSpace(char key)
{
    if (key == ' ' || key == '\t' || key == '\n' || key == '\v' || key == '\f' || key == '\r')
    {
        return 1;
    }

    return 0;
}