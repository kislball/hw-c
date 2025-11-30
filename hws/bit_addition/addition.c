#include "addition.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void intToComplement(int32_t number, int bits[BITS])
{
    for (int i = 0; i < BITS; i++) {
        bits[BITS - 1 - i] = (number >> i) & 1;
    }
}

void printBits(int bits[BITS])
{
    for (int i = 0; i < BITS; i++) {
        printf("%d ", bits[i]);
    }
}

int32_t complementToInt(const int bits[BITS])
{
    int32_t result = 0;

    for (int i = 0; i < BITS; i++) {
        result = (result << 1) | bits[i];
    }

    return result;
}

void addBits(const int a[BITS], const int b[BITS], int result[BITS])
{
    int carry = 0;

    for (int i = BITS - 1; i >= 0; i--) {
        int s = a[i] + b[i] + carry;
        result[i] = s & 1;
        carry = (s >> 1) & 1;
    }
}

int* allocateBits(void)
{
    int* result = calloc(BITS, sizeof(*result));
    assert(result != NULL && "Allocation failed");
    return result;
}
