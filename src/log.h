#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define SC_OKAY(message, ...) printf("[+] " message "\n", ##__VA_ARGS__)
#define SC_ERROR(message, ...) printf("[-] " message "\n", ##__VA_ARGS__)
#define SC_WARNING(message, ...) printf("[!] " message "\n", ##__VA_ARGS__)
#define SC_INFO(message, ...) printf("[I] " message "\n", ##__VA_ARGS__)

#endif