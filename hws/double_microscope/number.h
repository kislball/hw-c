#include <stdbool.h>
#include <stdint.h>

typedef struct {
    bool sign;
    uint16_t exponent;
    double mantissa;
} BinaryNumber;

BinaryNumber decodeNumber(double number);
