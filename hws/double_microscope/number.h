#include <stdbool.h>
#include <stdint.h>

typedef struct {
    bool sign;
    int16_t exponent;
    double mantissa;
} BinaryNumber;

BinaryNumber decodeNumber(double number);
