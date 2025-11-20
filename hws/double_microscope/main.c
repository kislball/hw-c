#include "number.h"
#include <assert.h>
#include <stdhw.h>
#include <stdio.h>

int main(void)
{
    double num = promptDouble("Введите число: ");
    BinaryNumber binNum = decodeNumber(num);

    printf("%c%.15g*2^%d\n", binNum.sign ? '-' : '+', binNum.mantissa, binNum.exponent);
    return 0;
}
