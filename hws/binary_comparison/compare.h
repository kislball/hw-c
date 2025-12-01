#pragma once

#include <stdint.h>

#define BITS 32

// Результат сравнения двух чисел
typedef enum {
    CompGreater,
    CompEqual,
    CompLess,
} ComparisonResult;

// Сравнивает два числа побитово
ComparisonResult compare(int32_t a, int32_t b);
