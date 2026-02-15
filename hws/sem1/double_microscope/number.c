#include "number.h"

BinaryNumber decodeNumber(double number)
{
    BinaryNumber result;
    uint64_t bits;

    bits = *(uint64_t*)(&number);

    result.sign = (bits >> 63) & 0x1;
    // В данном случае переход безопасен, так как отбрасываются 52 бита, остаётся 12 бит, что влезает в тип int16_t
    result.exponent = ((bits >> 52) & 0x7FF) - 1023; // NOLINT(cppcoreguidelines-narrowing-conversions)
    uint64_t mantissa = bits & 0xFFFFFFFFFFFFF;
    mantissa |= (1ULL << 52);
    result.mantissa = (double)mantissa / (double)(1ULL << 52);

    return result;
}
