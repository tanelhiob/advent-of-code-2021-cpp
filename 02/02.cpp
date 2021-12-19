#define _CRT_SECURE_NO_DEPRECATE

#include <chrono>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t micros()
{
    uint64_t us = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::
        now().time_since_epoch()).count();
    return us;
}

int main()
{
    uint64_t start = micros();

    FILE* input = fopen("input.txt", "r");
    const int bufferLength = 255;
    char buffer[bufferLength];

    int nic;
    int h = 0;
    int v = 0;

    int v2 = 0;

    char* stop;

    while (fgets(buffer, bufferLength, input)) {

        switch (buffer[0]) {
        case 'f':
            nic = strtol(&buffer[8], &stop, 10);
            h += nic;
            v2 += nic * v;
            break;
        case 'u':
            nic = strtol(&buffer[3], &stop, 10);
            v -= nic;
            break;
        case 'd':
            nic = strtol(&buffer[5], &stop, 10);
            v += nic;
            break;
        }
    }

    printf("%i\n", h * v); // 1815044
    printf("%i\n", h * v2); // 1739283308

    uint64_t end = micros();
    uint64_t diff = end - start;
    printf("time: %" PRIu64 "\n", diff);
}