#include <stdio.h>
#include <stdlib.h>

#define HELP 1
#define END 2
#define START 3
#define STEP 4

int main(int argc, char** argv) {
    int start = 0, end = 0, step = 1, i;
    if (argc == HELP) {
        printf("help\n");
    } else if (argc == END) {
        end = atoi(argv[1]);
    } else if (argc == START) {
        start = atoi(argv[1]);
        end = atoi(argv[2]);
    } else if (argc == STEP) {
        start = atoi(argv[1]);
        end = atoi(argv[2]);
        step = atoi(argv[3]);
    }
    for (i = start; i < end; i = i + step)
        printf("%d\n", i);
    return 0;
}