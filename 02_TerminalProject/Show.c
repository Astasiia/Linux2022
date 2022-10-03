#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define START_SIZE 128
#define COUNT_ARG 2
#define DELTA 2
#define SIZE_DATA 4
#define WIDTH 0
#define HEIGHT 1
#define POS_X 2
#define POS_Y 3

const int LEN_NUMBER = strlen("0000: ");

/* Чтение файла */
char *readFile(FILE *file) {
    int c, i = 0, size = START_SIZE;
    char *array = malloc(size * sizeof(char));
    while ((c = fgetc(file)) != EOF) {
        if (i == size - 1) {
            size = size * 2;
            array = realloc(array, size * sizeof(char));
        }
        array[i] = c;
        i++;
    }
    array[i] = '\0';
    return array;
}

/* Загрузка файла */
char *loadFile(char *name_of_file) {
    FILE *file = fopen(name_of_file, "r");
    if (!file)
        return NULL;
    char *content_file = readFile(file);
    fclose(file);
    return content_file;
}

/* Определение начальныз позиций строк в файле */
int *startStringOfFile(char *file) {
    int i = 0, str_no = 0, size = START_SIZE;
    int *start_string = malloc(size * sizeof(int));
    start_string[str_no] = 0; str_no++;
    while (file[i] != '\0') {
        if (str_no == size - 1) {
            size = size * 2;
            start_string = realloc(start_string, size * sizeof(int));
        }
        if (file[i] == '\n') {
            start_string[str_no] = i + 1; str_no++;
        }
        i++;
    }
    start_string[str_no] = -1;
    return start_string;
}

/* Обновление информациии о положении строк после нажатия клавиш */
int updatePosition(WINDOW *window, int *str, int *data, int pos) {
    int c, exit_flag = 0;
    switch (c = wgetch(window)) {
        case ' ':
            if (str[data[POS_Y] + pos] != -1) data[POS_Y]++;
            break;
        case 261:
            data[POS_X]++;
            break;
        case 260:
            if (data[POS_X] > 0) data[POS_X]--;
            break;
        case 27:
        case 'q':
            exit_flag = 1;
            break;
        default:
            break;
    }
    return exit_flag;
}

/* Инициализация данных об окне и положении информации */
int *initField() {
    int size = SIZE_DATA;
    int *data = malloc(size * sizeof(int));
    data[HEIGHT] = LINES - 2 * DELTA;
    data[WIDTH] = COLS - 2 * DELTA;
    data[POS_Y] = 0;
    data[POS_X] = 0;
    return data;
}

/* Вытаскивание нужной строки из файла с нужной поцизии */
char *selectStringFromFile(char *file, int *str, int *data, int pos) {
    int select_number = pos + data[POS_Y],
        length_str = (str[select_number + 1] == -1) ?
                strlen(&file[str[select_number]]) - data[POS_X]:
                str[select_number + 1] - str[select_number] - data[POS_X],
        length = length_str < (data[WIDTH] - LEN_NUMBER) ?
                length_str :
                data[WIDTH] - LEN_NUMBER;
    length = length < 0 ? 0 : length;
    char *select_str = malloc((length + 1) * sizeof(char));
    select_str = strncpy(select_str, &file[str[select_number] + data[POS_X]], length);
    select_str[length] = '\0';
    return select_str;
}

int main (int argc, char **argv) {
    if (argc < COUNT_ARG) {
        printf("!!! No filename !!!\n");
        return 1;
    }

    int i, exit_flag = 0;

    char *file = loadFile(argv[1]);
    int *start_string = startStringOfFile(file);

    initscr(); noecho(); cbreak();
    printw("Name file: %s", argv[1]);
    refresh();

    int *data = initField();
    WINDOW *work_field = newwin(data[HEIGHT], data[WIDTH], DELTA, DELTA);
    keypad(work_field, TRUE);
    scrollok(work_field, TRUE);

    while (1) {
        werase(work_field);
        for (i = 0; i < data[HEIGHT] - 2 && start_string[i + data[POS_Y]] != -1; i++) {
            char* new_str = selectStringFromFile(file, start_string, data, i);
            mvwprintw(work_field, i + 1, 1, "%4d: %s", i + data[POS_Y], new_str);
            free(new_str);
        }
        box(work_field, 0, 0);
        wrefresh(work_field);
        exit_flag = updatePosition(work_field, start_string, data, i);
        if (exit_flag) break;
    }
    werase(work_field); endwin();

    free(data); free(start_string); free(file);
    return 0;
}