#include "compare.h"

// Получить n-ый бит числа(отсчёт начинается с нуля)
int getBit(int number, int bitNumber)
{
    return (number >> bitNumber) & 1;
}

ComparisonResult compare(int a, int b)
{
    for (int i = 31; i >= 0; i--) {
        int aBit = getBit(a, i);
        int bBit = getBit(b, i);

        if (aBit > bBit)
            return CompGreater;
        else if (aBit < bBit)
            return CompLess;
    }
    return CompEqual;
}
