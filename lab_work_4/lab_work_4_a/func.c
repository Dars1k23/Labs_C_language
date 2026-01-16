#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#define DELIM " \t"
#define PROMT "|<*>_<*>| ->"
#include <string.h>
#include <time.h>

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
    char *s = strdup(str);
    int len_s = strlen(s);
    char *res = calloc(len_s + 1, sizeof(char));
    int pos = 0;
    char *word = strtok(s, DELIM);
    while (word != NULL) {
        int w_len = strlen(word);
        if (w_len == 0) {
            word = strtok(NULL, DELIM);
            continue;
        }
        int shift = n % w_len;
        for (int i = 0; i < w_len; i++) {
            res[pos + i] = word[(i + shift) % w_len];
        }
        pos += w_len;
        word = strtok(NULL, DELIM);
        if (word != NULL) {
            res[pos++] = ' ';
        }
    }
    free(s);
    res[pos] = '\0';
    return res;
}

int run(){
    int n = read_int_simple();
    char *input = readline(PROMT);
    while (input != NULL) {
        printf("\"%s\"\n", input);
	clock_t start = clock();
        char *output = my_func(input, n);
	clock_t end = clock();
	double time_spend = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Сдвинутая: \"%s\"\n", output);
	printf("Время выполнения функции: %.6f секнуд\n", time_spend);

        free(input);
        free(output);
        input = readline(PROMT);
    }
    return 0;
}
