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
ComparisonResult compare(uint32_t a, uint32_t b);
