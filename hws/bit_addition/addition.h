#pragma once
#include <assert.h>
#include <stdint.h>

#define BITS 32

// Переводит число в дополнительный код
void intToComplement(int32_t number, int bits[BITS]);
// Выводит число в дополнительном коде
void printBits(int bits[BITS]);
// Переводит число в дополнительном коде в число
int32_t complementToInt(const int bits[BITS]);
// Побитово складывает числа a и b
void addBits(const int a[BITS], const int b[BITS], int result[BITS]);
// Выделяет память под дополнительный код числа
int* allocateBits(void);
