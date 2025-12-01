#include "compare.h"
#include <stdint.h>

// Получить n-ый бит числа(отсчёт начинается с нуля)
int getBit(uint32_t number, int bitNumber)
{
    return (number >> bitNumber) & 1; // NOLINT в данном случае оправдано, т.к. значение бита либо 0 либо 1
}

ComparisonResult compare(uint32_t a, uint32_t b)
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
