#include "lexerCharTypes.h"
#include "types.h"

static const u64 bitSet[] = 
{
    // bits in these ranges should be set 123 - 126, 93 - 94, 91 - 91, 58 - 62, 33 - 47
    0x7C00FFFE00000000, //  0x7C 00 FF FE 00 00 00 00
    0x7800000068000000, // 0x78 00 00 00 68 00 00 00
    0,
    0,
};

int IsSingleCharToken(char key)
{
    u32 byteIndex = (u8)key / (sizeof(u64) * 8);
    u64 bitMask = ((u64)1 << (key % (sizeof(u64) * 8)));

    if (bitMask & bitSet[byteIndex])
    {
        return 1;
    }
    
    return 0;
}

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