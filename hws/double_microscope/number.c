#include "number.h"

BinaryNumber decodeNumber(double number)
{
    BinaryNumber result;
    uint64_t bits;
    
    bits = *(uint64_t*)(&number);
    
    result.sign = (bits >> 63) & 0x1;
    result.exponent = ((bits >> 52) & 0x7FF) - 1023;
    uint64_t mantissa = bits & 0xFFFFFFFFFFFFF;
	mantissa |= (1ULL << 52);
	result.mantissa = mantissa / (double)(1ULL << 52);
    
    return result;
}
