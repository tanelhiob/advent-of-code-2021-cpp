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

int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int fact(int num) {
    int sum = 0;
    for (int i = 1; i <= num; i++) {
        sum += i;
    }
    return sum;
}

int main()
{
    uint64_t timer_start = micros();

    int nic;

    FILE* input = fopen("input.txt", "r");
    const int bufferLength = 4096;
    char buffer[bufferLength];

    fgets(buffer, bufferLength, input);

    int crabs1[1500] = { 0 };
    int crabs2[1500] = { 0 };
    int crab;

    char* start = buffer;
    char* end;
    while (*start != '\0') {
        crab = strtol(start, &end, 10);
        
        for (nic = 0; nic < 1500; nic++) {
            crabs1[nic] += abs(nic - crab);
            crabs2[nic] += fact(abs(nic - crab));
        }

        start = end + 1;
    }

    int sum1 = INT_MAX;
    int sum2 = INT_MAX;
    for (nic = 0; nic < 1500; nic++) {
        if (crabs1[nic] < sum1) sum1 = crabs1[nic];
        if (crabs2[nic] < sum2) sum2 = crabs2[nic];
    }

    //int crabs[2048];
    //int crabIndex = 0;

    //char* start = buffer;
    //char* end;
    //while (*start != '\0') {
    //    crabs[crabIndex] = strtol(start, &end, 10);
    //    crabIndex++;
    //    start = end + 1;
    //}

    //// TODO: save as a frequency table to avoid logn
    //qsort(crabs, crabIndex, sizeof(int), cmp);

    //int median = crabs[crabIndex / 2];
    //int sum1 = 0;
    //int sum2 = 0;
    //int fuel;
    //for (nic = 0; nic < crabIndex; nic++) {
    //    fuel = abs(crabs[nic] - median);
    //    sum1 += fuel;
    //    sum2 += fact(fuel);
    //}

    printf("%d\n", sum1); // 352997
    printf("%d\n", sum2); // 101571302

    uint64_t timer_end = micros();
    uint64_t timer_diff = timer_end - timer_start;
    printf("time: %" PRIu64 "\n", timer_diff);
}