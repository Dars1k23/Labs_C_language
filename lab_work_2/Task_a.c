#include <stdio.h>
#include <math.h>


void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF){

    }
}

long double Calcul_rows(long  double x, int a);
int Chek_x_1(int res, char ch);
long double Chek_x_2(long double x);

int Chek_x_1(int res, char ch){
    if (res == 2 && ch == '\n') {
        return 0;
    }
    return 1;
}

long double Chek_x_2(long double x) {
    if (x >= -0.5L && x < 0.5L) {
        return 0;
    }
    return 1;
}

long double Calcul_rows(long  double x, int a) {
    long double result = x;
    long double term = x * x;
    int n = 1;
    int znam = 2;
    long double i = 0.0L;
    while (fabsl(term) > 1e-20L) {
        if (n == a) {
            break;
        }
        long double chisl = term * (3 + i) * x;
        long double del = chisl / znam;
        term += del;
        n++;
        i += 2;
        znam *= (znam + 1);
    }
    result += term;
    return result;
}

int main() {
    long double x;
    int a;
    char ch;
    int res;
    int res_2;
    long double new_res;
    long double num;

    printf("Введите x в диапазоне [-0.5, 0.5): ");
    res = scanf("%Lf%c", &x, &ch);
    res = Chek_x_1(res, ch);
    res_2 = Chek_x_2(x);

    while (res == 1 || res_2 == 1) {
        if (res == 1) {
            printf("Некорректная форма входных данных!\n");
            clear_input_buffer();
            printf("Введите x в диапазоне [-0.5, 0.5): ");
            res = scanf("%Lf%c", &x, &ch);
            res = Chek_x_2(x);
            res = Chek_x_1(res, ch);

        }
        if (res_2 == 1) {
            printf("Ошибка: x должен быть в диапазоне [-0.5, 0.5)\n");
            clear_input_buffer();
            printf("Введите x в диапазоне [-0.5, 0.5): ");
            res = scanf("%Lf%c", &x, &ch);
            res_2 = Chek_x_2(x);
        }
    }

    printf("Введите число рядов: ");
    while (scanf("%d", &a) != 1) {
        printf("Некорректный ввод! Введите число рядов заново: ");
        clear_input_buffer();
    }
    num = Calcul_rows(x, a);
    new_res = x / sqrt(1 - 2*x);

    printf("%.15Lf\n", num);
    printf("%.15Lf\n", new_res);
    printf("%.15Lf\n", fabsl(new_res - num));

    return 0;
}
