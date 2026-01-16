#include <stdio.h>
#include <math.h>

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {

    }
}

long double power_of_ten(int exp) {
    long double result = 1.0L;
    if (exp > 0) {
        for (int i = 0; i < exp; i++) {
            result *= 10.0L;
        }
    }
    else{
        for (int i = 0; i < -exp; i++) {
            result /= 10.0L;
        }
    }
    return result;
}

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


long double Calcul_rows(long double x, long double epsilon, int *step) {
    long double result = x;
    long double term = x * x;
    int n = 1;
    result += term;
    while (fabsl(term) > epsilon) {
        term = term * x * (2 * n - 1) / n;
        result += term;
        n++;
    }
    *step = n;
    return result;
}

int main() {
    long double x;
    char ch;
    int res, res_2;
    int precision;
    long double epsilon, num, new_res;
    int step;

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
            res = Chek_x_1(res, ch);
        }
        if (res_2 == 1) {
            printf("Ошибка: x должен быть в диапазоне [-0.5, 0.5)\n");
            clear_input_buffer();
            printf("Введите x в диапазоне [-0.5, 0.5): ");
            res = scanf("%Lf%c", &x, &ch);
            res_2 = Chek_x_2(x);
        }
	if (res == EOF){
		printf("EOF");
		break;
	}
    }

    printf("Введите число знаков после запятой (точность): ");
    while (scanf("%d", &precision) != 1 || precision < 0) {
        printf("Некорректный ввод! Введите число заново: ");
        clear_input_buffer();
    }

    epsilon = power_of_ten(-precision);
    num = Calcul_rows(x, epsilon, &step);
    new_res = x / sqrtl(1 - 2*x);

    printf("Сумма ряда с точностью до %d знаков после запятой: %.*Lf\n", precision, precision, num);
    printf("Точное значение функции: %.*Lf\n", precision, new_res);
    printf("Разница: %.*Lf\n", precision, new_res - num);
    printf("Переход за заданную точность произошел на шаге %d\n", step);

    return 0;
}
