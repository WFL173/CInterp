#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "log.h"
#include "lexer.h"

typedef struct EntireFile
{
    u8* Contents;
    int Size; // this variable is equal to fileSize + 1. The extra one is from the '\0' character.
} EntireFile;

EntireFile ReadEntireFile(char* fileName)
{
    EntireFile result = {0};
    FILE* file = fopen(fileName, "rb");
    if (!file)
    {
        SC_ERROR("file %s could not be found", fileName);
        return result;
    }

    fseek(file, 0, SEEK_END);
    result.Size = ftell(file);
    fseek(file, 0, SEEK_SET);

    SC_INFO("file size %d", result.Size);
    result.Contents = malloc(result.Size + 1);
    fread(result.Contents, result.Size, 1, file);
    result.Contents[result.Size++] = '\0';
    fclose(file);

    return result;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("usage: ");
        return 1;
    }

    EntireFile source = ReadEntireFile(argv[1]);
    Lexer lexer = LexerInit(source.Contents, source.Size);
    LexerTokenize(&lexer);
   
    free(source.Contents);
    return 0;
}