#include <stdio.h>
#include <stdlib.h>

#define START_SIZE 128;

/* Чтение строки с потока ввода от пользователя
 * Посимвольное чтение в динамический массив */
char *read_string();

char *read_string() {
    int c, i = 0, size = START_SIZE;
    char *array = malloc(size * sizeof(char));
    while ((c = getchar()) != EOF) {
        if (c == '\n') break;
        if (i == size - 1) {
            size = size * 2;
            array = realloc(array, size);
        }
        array[i] = c;
        i++;
    }
    array[i] = '\0';
    return array;
}

int main() {
    char *entered_string = read_string();
    printf("Hello, %s!\n", entered_string);
    free(entered_string);
    return 0;
}
