#include <stdio.h>

int Remake(int);

int main()
{
	int num;
	char ch;
	int res;
	printf("Введите число: ");
	res = scanf("%d%c", &num, &ch);
	if (res == 2 && ch == '\n')
	{
		printf("Вы ввели корректное число!\n");
		num = Remake(num);
		printf("%d", num);
	}
	else
	{
		printf("Не правильный формат данных!");
	}
	
	return 0;
}

int Remake(int num)
{
	int res = 0;
	int mul = 1;
	while (num > 0)
	{
		res = res + (num % 2) * mul;
		num = num / 2;
		mul = mul * 10;
	}
	return res;
}
