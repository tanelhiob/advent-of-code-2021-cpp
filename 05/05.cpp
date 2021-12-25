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

void printMap(int map[1000][1000]) {    
        for (int y = 0; y < 10; y++) {
            for (int x = 0; x < 10; x++) {
            if (map[x][y] == 0) {
                printf(".");
            }
            else {
                printf("%i", map[x][y]);
            }
        }
        printf("\n");
    }
}

int main()
{
    uint64_t timer_start = micros();

    int nic;

    FILE* input = fopen("input.txt", "r");
    const int bufferLength = 128;
    char buffer[bufferLength];
  
    int sum1 = 0;
    int map1[1000][1000] = { 0 };    
    int x1, y1, x2, y2;

    int sum2 = 0;
    int map2[1000][1000] = { 0 };    

    while (fgets(buffer, bufferLength, input)) {

        sscanf(buffer, "%i,%i -> %i,%i", &x1, &y1, &x2, &y2);
        
        if (x1 == x2) {
            if (y1 <= y2) {
                while (y1 <= y2) {
                    map1[x1][y1]++;                                        
                    if (map1[x1][y1] == 2) {
                        sum1++;
                    }
                    map2[x1][y1]++;
                    if (map2[x1][y1] == 2) {
                        sum2++;
                    }
                    y1++;
                }
            }
            else {
                while (y2 <= y1) {
                    map1[x1][y2]++;                    
                    if (map1[x1][y2] == 2) {
                        sum1++;
                    }
                    map2[x1][y2]++;
                    if (map2[x1][y2] == 2) {
                        sum2++;
                    }
                    y2++;
                }
            }
        }
        else if (y1 == y2) {
            if (x1 <= x2) {
                while (x1 <= x2) {
                    map1[x1][y1]++;
                    if (map1[x1][y1] == 2) {
                        sum1++;
                    }
                    map2[x1][y1]++;
                    if (map2[x1][y1] == 2) {
                        sum2++;
                    }
                    x1++;
                }
            }
            else {
                while (x2 <= x1) {
                    map1[x2][y1]++;
                    if (map1[x2][y1] == 2) {
                        sum1++;
                    }
                    map2[x2][y1]++;
                    if (map2[x2][y1] == 2) {
                        sum2++;
                    }
                    x2++;
                }
            }
        }
        else {
            if (x1 < x2) {
                if (y1 < y2) {
                    while (x1 <= x2) {
                        map2[x1][y1]++;
                        if (map2[x1][y1] == 2) {
                            sum2++;
                        }
                        x1++;
                        y1++;
                    }
                }
                else {
                    while (x1 <= x2) {
                        map2[x1][y1]++;
                        if (map2[x1][y1] == 2) {
                            sum2++;
                        }
                        x1++;
                        y1--;
                    }
                }
            }
            else {
                if (y1 < y2) {
                    while (y1 <= y2) {
                        map2[x1][y1]++;
                        if (map2[x1][y1] == 2) {
                            sum2++;
                        }
                        x1--;
                        y1++;
                    }
                }
                else {
                    while (y2 <= y1) {
                        map2[x1][y1]++;
                        if (map2[x1][y1] == 2) {
                            sum2++;
                        }
                        x1--;
                        y1--;
                    }
                }
            }
        }

        //printMap(map2);
        //printf("\n");
    }

    printf("%d\n", sum1); // 7468
    printf("%d\n", sum2); // 22364

    uint64_t timer_end = micros();
    uint64_t timer_diff = timer_end - timer_start;
    printf("time: %" PRIu64 "\n", timer_diff);
}