#define BITS 32

// Результат сравнения двух чисел
typedef enum {
    CompGreater,
    CompEqual,
    CompLess,
} ComparisonResult;

// Сравнивает два числа побитово
ComparisonResult compare(int a, int b);
