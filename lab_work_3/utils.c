#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void clear_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void ad_ellement(int **list, int *size, int *cap, int new_ellement) {
    if (*size == *cap) {
        int new_cap = (*cap == 0) ? 1 : (*cap * 2);
        int *new_list = realloc(*list, new_cap * sizeof(int));
        if (new_list == NULL) {
            printf("Ошибка выделения памяти!\n");
            return;
        }
        *list = new_list;
        *cap = new_cap;
    }
    (*list)[*size] = new_ellement;
    (*size)++;
}

int sum_digits(int num) {
    int sum = 0;
    if (num < 0) num = -num;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int* my_task(int **list, int *size, int *new_size, int M) {
    int *new_list = malloc(*size * sizeof(int));
    if (!new_list) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    *new_size = 0;

    for (int i = 0; i < *size; ) {
        if (sum_digits((*list)[i]) == M) {
            new_list[*new_size] = (*list)[i];
            (*new_size)++;
            // Удаляем из исходного массива
            for (int j = i; j < *size - 1; j++) {
                (*list)[j] = (*list)[j + 1];
            }
            (*size)--;
        } else {
            i++;
        }
    }
    return new_list;
}

void print_array(int *list, int size) {
    printf("Массив: ");
    if (size == 0) {
        printf("пуст\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

int run() {
    int *list = NULL;
    int size = 0;
    int cap = 0;
    char choice;

    while (1) {
        printf("\nМеню:\n");
        printf("a - Инициализация массива\n");
        printf("b - Вставка нового элемента\n");
        printf("c - Удаление элемента\n");
        printf("d - Индивидуальное задание\n");
        printf("e - Вывод массива\n");
        printf("q - Выход\n");
        printf("Выберите пункт: ");
        
        if (scanf(" %c", &choice) != 1) {
            printf("Ошибка чтения пункта меню\n");
            clear_input();
            continue;
        }
        clear_input();
        if (choice == 'q') break;

        switch (choice) {
            case 'a': {
                int n, val;
                printf("Введите размер массива (> 0): ");
                if (scanf("%d", &n) != 1 || n <= 0) {
                    printf("Неверный размер (должен быть > 0)\n");
                    clear_input();
                    break;
                }
                clear_input();

                free(list);
                list = malloc(n * sizeof(int));
                if (!list) {
                    printf("Ошибка выделения памяти\n");
                    exit(1);
                }
                cap = n;
                size = 0;
                
                printf("Введите %d элементов:\n", n);
                for (int i = 0; i < n; i++) {
                    printf("Элемент %d: ", i + 1);
                    if (scanf("%d", &val) != 1) {
                        printf("Неверный ввод числа\n");
                        clear_input();
                        i--;  // Повторяем этот элемент
                        if (i < 0) i = 0;
                    } else {
                        clear_input();
                        list[i] = val;
                        size++;
                    }
                }
                print_array(list, size);
                break;
            }
            
            case 'b': {
                int val, idx;
                printf("Введите индекс (>=0) и значение: ");
                if (scanf("%d %d", &idx, &val) != 2) {
                    printf("Неверный ввод (нужен индекс и значение)\n");
                    clear_input();
                    break;
                }
                clear_input();

                if (idx < 0) {
                    printf("Индекс не может быть отрицательным\n");
                    break;
                }
                if (idx > size) idx = size;
                
                ad_ellement(&list, &size, &cap, 0);  // Резервируем место
                for (int i = size - 1; i > idx; i--) {
                    list[i] = list[i - 1];
                }
                list[idx] = val;
                print_array(list, size);
                break;
            }
            
            case 'c': {
                int idx;
                printf("Введите индекс для удаления (0-%d): ", size ? size-1 : 0);
                if (scanf("%d", &idx) != 1) {
                    printf("Неверный ввод индекса\n");
                    clear_input();
                    break;
                }
                clear_input();

                if (idx < 0 || idx >= size) {
                    printf("Неверный индекс (0-%d)\n", size ? size-1 : 0);
                    break;
                }
                
                for (int i = idx; i < size - 1; i++) {
                    list[i] = list[i + 1];
                }
                size--;
                print_array(list, size);
                break;
            }
            
            case 'd': {
                int M;
                printf("Введите число M (> 0): ");
                if (scanf("%d", &M) != 1) {
                    printf("Неверный ввод M\n");
                    clear_input();
                    break;
                }
                clear_input();

                if (M <= 0) {
                    printf("M должен быть больше 0\n");
                    break;
                }
                
                int new_size;
                int *new_list = my_task(&list, &size, &new_size, M);
                printf("Исходный массив после удаления:\n");
                print_array(list, size);
                printf("Новый массив (сумма цифр = %d):\n", M);
                print_array(new_list, new_size);
                free(new_list);
                break;
            }
            
            case 'e': {
                print_array(list, size);
                break;
            }
            
            default:
                printf("Неверный пункт меню (a-e, q)\n");
        }
    }

    free(list);
    return 0;
}
