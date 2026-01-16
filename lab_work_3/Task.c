#include "my_task.h"
#include <stdio.h>     
#include <stdlib.h> 
#include <stddef.h>    
#include "errors.h"    
#include "array.h"

int sum_digits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}


error_t my_task(int *list, int size, int M, int **new_list, int *new_size) {
    if (size == 0) return EMPTY_ARRAY;
    
    *new_list = malloc(size * sizeof(int));
    if (!*new_list) return MEMORY_ERROR;
    
    *new_size = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] % M == 0) {
            (*new_list)[*new_size] = list[i];
            (*new_size)++;
        }
    }
    return SUCCESS;
}

int run() {
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
                cap = n;
                size = 0;
                for (int i = 0; i < n; i++) {
                    printf("Введите элемент %d: ", i+1);
                    if (scanf("%d", &val) != 1) {
                        printf("Неверный ввод\n");
                        i--;
                        while(getchar()!='\n');
                    } else {
                        list[i] = val;
                        size++;
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

                int res = add_element(&list, &size, &cap, val);
                if (res != 0) {
                    fprintf(stderr, "Не удалось добавить элемент\n");
                    break;
                }

                
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
               int M;
               if (scanf("%d", &M) != 1) break;
    
               int *new_list = NULL;
               int new_size = 0;
               error_t err = my_task(list, size, M, &new_list, &new_size);
               if (err == SUCCESS && new_list) {
                   printf("Новый массив: ");
                   print_array(new_list, new_size);
               free(new_list);
             } 
	       else {
                   printf("Ошибка задания: %s\n", error_message(err));
    }
    break;
}


            case 'e': {
                if (size == 0) {
                    printf("Массив пуст\n");
                } else {
                    print_array(list, size);
                }
                break;
            }
            default:
                printf("Неверный пункт меню\n");
        }
    }

    free(list);
    return 0;
}
