#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAP_LENGTH 8

int counter = 0;
int list[MAP_LENGTH];
int curr = 0;

int isValid(int pos)
{
    int ret = 1;
    for (int i = 0; i < MAP_LENGTH; i++) {
        int x = list[i];
        if (x == -1) {
            continue;
        }
        if ((pos & 007) == (x & 007) ||
            ((pos & 007) > (x & 007) && (pos - x) % 011 == 0 && (pos - x) / 011 == ((pos & 070) >> 3) - ((x & 070) >> 3)) ||
            ((pos & 007) < (x & 007) && (pos - x) % 007 == 0 && (pos - x) / 007 == ((pos & 070) >> 3) - ((x & 070) >> 3))) {
                ret = 0;
                break;
        }
    }
    return ret;
}

void generate(int row)
{
    for (int i = 0; i < MAP_LENGTH; i++) {
        char buffer[10];
        char *ptr;
        sprintf(buffer, "0%d%d", row, i);
        int pos = (int)strtol(buffer, &ptr, 8);
        if (row == 0) {
            curr = 0;
            memset(list, -1, sizeof(list));
        }
        if (isValid(pos)) {
            list[curr++] = pos;
            if (curr == MAP_LENGTH) {
                counter++;
                printf("COUNTER = %d\n", counter);
                printf("Current list:");
                for (int i = 0; i < MAP_LENGTH; i++) {
                    printf(" %02o", list[i]);
                }
                printf("\n");
                printf("----------------------------\n");
                list[--curr] = -1;
                list[--curr] = -1;
                return ;
            } else {
                generate(row + 1);
            }
        }
    }
    if (curr != 0) {
        list[--curr] = -1;
    }
}

int main()
{
    generate(0);
    printf("There are in total %d results.\n", counter);
    return 0;
}