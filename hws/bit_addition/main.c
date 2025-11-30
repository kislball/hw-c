#include "addition.h"
#include <assert.h>
#include <stdio.h>
#include <stdhw.h>
#include <stdlib.h>

int main(void)
{
	int a = prompt("a=");
	int b = prompt("b=");

	int *aComplement = allocateBits();
	int *bComplement = allocateBits();

	intToComplement(a, aComplement);
	intToComplement(b, bComplement);

	printf("a=  ");
	printBits(aComplement);
	printf("\nb=  ");
	printBits(bComplement);

	int *result = allocateBits();
	addBits(aComplement, bComplement, result);

	printf("\na+b=");
	printBits(result);

	int realResult = complementToInt(result);
	printf("\na+b=%d\n", realResult);

	assert(a + b == realResult);

	return 0;
}
