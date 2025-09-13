#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Функция возвращает true если деление прошло успешно, false в ином случае
// По указателю result будет записано частное целочисленного деления a / b
bool divInt(int a, int b, int* result)
{
    if (a == b) {
        *result = 1;
        return true;
    }

    if (b == 0) {
        return false;
    }

    if (a == 0) {
        *result = 0;
        return true;
    }

    int abs_a = abs(a);
    int abs_b = abs(b);

    *result = 0;
    while (abs_a >= abs_b) {
        abs_a -= abs_b;
        *result += 1;
    }

    if (a * b < 0) {
        *result += 1;
        *result *= -1;
    }

    return true;
}

void divAndPrint(int a, int b)
{
    int result = 0;
    if (divInt(a, b, &result)) {
        printf("%d // %d = %d\n", a, b, result);
    } else {
        printf("Деление невозможно\n");
    }
}

int prompt(char* data)
{
    int ans = 0;
    printf("%s", data);
    scanf("%d", &ans);
    return ans;
}

int main(void)
{
    int a = prompt("Введите делимое: ");
    int b = prompt("Введите делитель: ");
    divAndPrint(a, b);
}
