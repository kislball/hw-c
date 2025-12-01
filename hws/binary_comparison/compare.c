#include "compare.h"
#include <stdint.h>

// Получить n-ый бит числа(отсчёт начинается с нуля)
int getBit(int number, int bitNumber)
{
    return (number >> bitNumber) & 1;
}

ComparisonResult compare(int32_t a, int32_t b)
{
    for (int i = BITS - 1; i >= 0; i--) {
        int aBit = getBit(a, i);
        int bBit = getBit(b, i);

        if (aBit > bBit)
            return CompGreater;
        else if (aBit < bBit)
            return CompLess;
    }
    return CompEqual;
}
