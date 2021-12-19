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

    const int commonsLength = 12;
    int powersOfTwo[commonsLength] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048 };
    int commons[commonsLength] = { 0 };
    int index = 0;
    int nic;
    
    int previousNode;
    int nextNode;
    int tree[4096] = { 0 };

    FILE* input = fopen("input.txt", "r");
    const int bufferLength = 255;
    char buffer[bufferLength];
    while (fgets(buffer, bufferLength, input)) {

        for (nic = 0; nic < commonsLength; nic++) {
            commons[nic] += buffer[nic] - 48;
        }

        if (buffer[0] == '1') {
            tree[1]++;
        }
        else {
            tree[1]--;
        }

        previousNode = 1;
        for (nic = 1; nic < commonsLength; nic++) {
            nextNode = previousNode * 2 + buffer[nic - 1] - 48;
            if (buffer[nic] == '1')
            {
                tree[nextNode]++;
            }
            else {
                tree[nextNode]--;
            }
            previousNode = nextNode;
        }

        index++;
    }

    int gamma = 0;
    int threshold = index / 2;
    for (nic = 0; nic < commonsLength; nic++) {
        if (commons[nic] > threshold)
            gamma += powersOfTwo[commonsLength - nic - 1];
    }
    int epsilon = ~gamma & 4095;


    int value;
    int node = 1;
    int oxygen = 0;
    for (nic = 0; nic < commonsLength; nic++) {
        value = tree[node] >= 0 ? 1 : 0;
        oxygen += value * powersOfTwo[12 - 1 - nic];
        node = node * 2 + value;
    }

    node = 1;
    int co2 = 0;
    for (nic = 0; nic < commonsLength; nic++) {
        value = tree[node] > 0 ? 0 : 1;
        co2 += value * powersOfTwo[12 - 1 - nic];
        node = node * 2 + value;
    }

    // TODO: seconds solution is not correct

    // proovime veel korra CI

    printf("%i\n", gamma * epsilon); // 3895776
    printf("%i\n", oxygen * co2); // 7928162   

    uint64_t end = micros();
    uint64_t diff = end - start;
    printf("time: %" PRIu64 "\n", diff);
}