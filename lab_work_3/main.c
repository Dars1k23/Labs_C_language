#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() {
    int *list = NULL;
    int size = 0;
    int cap = 0;
    char choice;
    int M;

    while (1) {
        printf("\nМеню:\n");
        printf("a - Инициализация массива\n");
        printf("b - Вставка нового элемента\n");
        printf("c - Удаление элемента\n");
        printf("d - Индивидуальное задание\n");
        printf("e - Вывод массива\n");
        printf("q - Выход\n");
        printf("Выберите пункт: ");
        if (scanf(" %c", &choice) != 1) break;
        if (choice == 'q') break;

        switch (choice) {
            case 'a': {
                int n, val;
                printf("Введите размер массива: ");
                if (scanf("%d", &n) != 1 || n < 0) {
                    printf("Неверный ввод\n");
                    break;
                }
                free(list);
                list = malloc(n * sizeof(int));
                if (!list) {
                    printf("Ошибка выделения памяти\n");
                    exit(1);
                }
                size = n; cap = n;
                for (int i = 0; i < n; i++) {
                    printf("Введите элемент %d: ", i+1);
                    if (scanf("%d", &val) != 1) {
                        printf("Неверный ввод\n");
                        i--;
                        while(getchar()!='\n');
                    } else {
                        list[i] = val;
                    }
                }
                print_array(list, size);
                break;
            }
            case 'b': {
                int val, idx;
                printf("Введите индекс и значение для вставки: ");
                if (scanf("%d %d", &idx, &val) != 2) {
                    printf("Неверный ввод\n");
                    break;
                }
                if (idx > size) idx = size;
                ad_ellement(&list, &size, &cap, 0);
                for (int i = size - 1; i > idx; i--) {
                    list[i] = list[i - 1];
                }
                list[idx] = val;
                print_array(list, size);
                break;
            }
            case 'c': {
                int idx;
                printf("Введите индекс для удаления: ");
                if (scanf("%d", &idx) != 1 || idx < 0 || idx >= size) {
                    printf("Неверный индекс\n");
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
                printf("Введите число M: ");
                if (scanf("%d", &M) != 1) break;
                int new_size;
                int *new_list = my_task(&list, &size, &new_size, M);
                printf("Исходный массив после удаления:\n");
                print_array(list, size);
                printf("Новый массив из чисел с суммой цифр = %d:\n", M);
                print_array(new_list, new_size);
                free(new_list);
                break;
            }
            case 'e': {
                print_array(list, size);
                break;
            }
            default:
                printf("Неверный пункт меню\n");
        }
    }

    free(list);
    return 0;
}
