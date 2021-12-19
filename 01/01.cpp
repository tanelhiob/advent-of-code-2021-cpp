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

    int currentDepth;
    int previousDepth = INT_MAX;
    int counter = 0;

    int windowedPrevious = INT_MAX;
    int windowedCounter = 0;
    int window[3] = { 0, 0, 0 };
    int index = 0;
    int sum = 0;

    while (fgets(buffer, bufferLength, input)) {
        currentDepth = atoi(buffer);

        if (currentDepth > previousDepth)
            counter++;

        previousDepth = currentDepth;

        window[index % 3] = currentDepth;
        sum = window[0] + window[1] + window[2];

        if (index > 2 && sum > windowedPrevious)
            windowedCounter++;
 
        windowedPrevious = sum;

        index++;
    }
 
    printf("%i\n", counter); // 1462
    printf("%i\n", windowedCounter); // 1497

    uint64_t end = micros();
    uint64_t diff = end - start;
    printf("time: %" PRIu64 "\n", diff);
}