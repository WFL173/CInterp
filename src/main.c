#include <stdio.h>
#include <stdlib.h>

#define SC_OKAY(message, ...) printf("[+] " message "\n", ##__VA_ARGS__)
#define SC_ERROR(message, ...) printf("[-] " message "\n", ##__VA_ARGS__)
#define SC_WARNING(message, ...) printf("[!] " message "\n", ##__VA_ARGS__)
#define SC_INFO(message, ...) printf("[I] " message "\n", ##__VA_ARGS__)

typedef struct EntireFile
{
    char* Contents;
    int Size; // this variable is equal to fileSize + 1. The extra one is from the '\0' character.
} EntireFile;

EntireFile ReadEntireFile(char* fileName)
{
    EntireFile result = {0};
    FILE* file = fopen(fileName, "r");
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

int main(int argc, char** argv[])
{
    printf("test \n");
    return 0;
}