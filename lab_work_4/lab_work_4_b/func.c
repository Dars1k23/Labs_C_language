#include <stdio.h>
#include <stdlib.h>
#define PROMPT "|<*>_<*>| ->"
#define DELIM " \t"
#include <time.h>
#include "my_string.h"

int read_int_simple() {
    int n;
    char ch;
    printf("Введите колличество сдвигов: ");
    while (scanf("%d%c", &n, &ch) != 2 || ch != '\n') {
        printf("Ошибка! Только число: ");
        while (getchar() != '\n');
    }
    return n;
}

char *my_func(const char *str, int n) {
    char *s = my_strdup(str);
    int len_s = my_strlen(s);
    char *res = calloc(len_s + 1, sizeof(char));
    int pos = 0;
    char *word = my_strtok(s, DELIM);
    while (word != NULL) {
        int w_len =my_strlen(word);
        if (w_len == 0) {
            word = my_strtok(NULL, DELIM);
            continue;
        }
        int shift = n % w_len;
        for (int i = 0; i < w_len; i++) {
            res[pos + i] = word[(i + shift) % w_len];
        }
        pos += w_len;
        word = my_strtok(NULL, DELIM);
        if (word != NULL) {
            res[pos++] = ' ';
        }
    }
    free(s);
    res[pos] = '\0';
    return res;
}


int run() {
	clock_t start = clock();
    int n = read_int_simple();
    char *input = my_readline();
    while (input != NULL) {
        printf("\"%s\"\n", input);
        char *output = my_func(input, n);
        printf("Сдвинутая: \"%s\"\n", output);
	free(input);
        free(output);
        input = my_readline();
    }
    clock_t end = clock();
    double time_spend = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", time_spend);
    return 0;
}
