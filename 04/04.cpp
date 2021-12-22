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

int placeNumber(int board[5][5][2], int number, int index) {
    int sum = 0;
    bool isWon = false;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            if (isWon == false && board[y][x][0] == number) {
                board[y][x][1] = 1;

                if (index >= 2) {
                    
                    if (board[(y + 1) % 5][x][1]
                        + board[(y + 2) % 5][x][1]
                        + board[(y + 3) % 5][x][1]
                        + board[(y + 4) % 5][x][1] == 4) {
                        isWon = true;
                    }

                    if (board[y][(x + 1) % 5][1]
                        + board[y][(x + 2) % 5][1]
                        + board[y][(x + 3) % 5][1]
                        + board[y][(x + 4) % 5][1] == 4) {
                        isWon = true;
                    }
                }
            }
            else if (board[y][x][1] == false) {
                sum += board[y][x][0];
            }
        }
    }

    if (isWon) {
        return sum * number;
    }
    else {
        return -1;
    }
}

int main()
{
    uint64_t timer_start = micros();

    int nic;

    FILE* input = fopen("input.txt", "r");
    const int bufferLength = 512;
    char buffer[bufferLength];

    int amountOfNumbers = 0;
    int numbers[128];
    char* start = buffer;
    char* end;
    fgets(buffer, bufferLength, input);    
    while (*start != '\0') {
        numbers[amountOfNumbers] = strtol(start, &end, 10);
        start = end + 1;
        amountOfNumbers++;
    }
    fgets(buffer, bufferLength, input);

    int board[5][5][2];
    int index = 0;
    int sum;
    int fastestBoard[2] = { 100 };
    int slowestBoard[2] = { 0 };

    while (fgets(buffer, bufferLength, input)) {        
        
        if (buffer[0] == '\n') {
            index = 0;

            for (nic = 0; nic < amountOfNumbers; nic++) {  
                sum = placeNumber(board, numbers[nic], nic);
                if (sum >= 0) {
                    if (fastestBoard[0] > nic) {
                        fastestBoard[0] = nic;
                        fastestBoard[1] = sum;
                    }
                    
                    if (slowestBoard[0] < nic) {
                        slowestBoard[0] = nic;
                        slowestBoard[1] = sum;
                    }

                    break;
                }
            }
        }
        else {
            board[index][0][1] = 0;
            board[index][1][1] = 0;
            board[index][2][1] = 0;
            board[index][3][1] = 0;
            board[index][4][1] = 0;
            sscanf(buffer, "%d %d %d %d %d", &board[index][0][0], &board[index][1][0], &board[index][2][0], &board[index][3][0], &board[index][4][0]);
            index++;
        }
    }

    for (nic = 0; nic < amountOfNumbers; nic++) {
        sum = placeNumber(board, numbers[nic], nic);
        if (sum >= 0) {
            if (fastestBoard[0] > nic) {
                fastestBoard[0] = nic;
                fastestBoard[1] = sum;
            }
            if (slowestBoard[0] < nic) {
                slowestBoard[0] = nic;
                slowestBoard[1] = sum;
            }
            break;
        }
    }


    printf("%i\n", fastestBoard[1]); // 32844
    printf("%i\n", slowestBoard[1]); // 32844

    uint64_t timer_end = micros();
    uint64_t timer_diff = timer_end - timer_start;
    printf("time: %" PRIu64 "\n", timer_diff);
}