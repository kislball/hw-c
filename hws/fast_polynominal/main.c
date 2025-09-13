#include <stdio.h>

int CalculatePolynominal(int x)
{
    int x2 = x * x;
    return (x2 + x) * (x2 + 1) + 1;
}

int main(void)
{
    int input = 0;
    scanf("%d", &input);

    int value = CalculatePolynominal(input);

    printf("x^4 + x^3 + x^2 + x + 1 = %d при x = %d\n", value, input);
    return 0;
}
