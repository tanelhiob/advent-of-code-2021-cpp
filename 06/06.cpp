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
    uint64_t timer_start = micros();

    int nic;
    
    long long fishies[9] = { 0 };
    long long tmp = LLONG_MAX;

    FILE* input = fopen("input.txt", "r");
    const int bufferLength = 1024;
    char buffer[bufferLength];

    fgets(buffer, bufferLength, input);

    char* start = buffer;
    char* end;
    while (*start != '\0') {
        fishies[strtol(start, &end, 10)]++;
        start = end + 1;
    }


    for (nic = 0; nic < 80; nic++) {
        tmp = fishies[0];
        fishies[0] = fishies[1];
        fishies[1] = fishies[2];
        fishies[2] = fishies[3];
        fishies[3] = fishies[4];
        fishies[4] = fishies[5];
        fishies[5] = fishies[6];
        fishies[6] = tmp + fishies[7];
        fishies[7] = fishies[8];
        fishies[8] = tmp;
    }

    long long sum1 = fishies[0] +
        fishies[1] +
        fishies[2] +
        fishies[3] +
        fishies[4] +
        fishies[5] +
        fishies[6] +
        fishies[7] +
        fishies[8];

    for (; nic < 256; nic++) {
        tmp = fishies[0];
        fishies[0] = fishies[1];
        fishies[1] = fishies[2];
        fishies[2] = fishies[3];
        fishies[3] = fishies[4];
        fishies[4] = fishies[5];
        fishies[5] = fishies[6];
        fishies[6] = tmp + fishies[7];
        fishies[7] = fishies[8];
        fishies[8] = tmp;
    }

    long long sum2 = fishies[0] +
        fishies[1] +
        fishies[2] +
        fishies[3] +
        fishies[4] +
        fishies[5] +
        fishies[6] +
        fishies[7] +
        fishies[8];

    printf("%" PRId64 "\n", sum1); // 349549
    printf("%" PRId64 "\n", sum2); // 1589590444365


    uint64_t timer_end = micros();
    uint64_t timer_diff = timer_end - timer_start;
    printf("time: %" PRIu64 "\n", timer_diff);
}