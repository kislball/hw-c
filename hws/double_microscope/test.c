#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "number.h"
#include <time.h>
#include <math.h>

#define TOTAL_TESTS 1000

double randDouble(double low, double high)
{
    return ((double)rand() * (high - low)) / (double)RAND_MAX + low;
}

void checkInBoundaries(double low, double high)
{
    for (int i = 0; i < TOTAL_TESTS; i++) {
        double num = randDouble(low, high);
        BinaryNumber binNum = decodeNumber(num);
        assert((num >= 0 ? !binNum.sign : binNum.sign) && "Sign must match");
        int exp = 0;
        double mantissa = frexp(fabs(num), &exp);
        exp--;
        assert(exp == binNum.exponent && "Exponents must match");
    }
}

int main()
{
    srand((unsigned int)time(0));

    checkInBoundaries(-10000, 10000);
    checkInBoundaries(-1, 1);

    return 0;
}