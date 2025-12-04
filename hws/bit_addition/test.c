#include "addition.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TESTS 1000

bool checkForTwoNumbers(int a, int b)
{
    int* aCompl = allocateBits();
    intToComplement(a, aCompl);

    int* bCompl = allocateBits();
    intToComplement(b, bCompl);

    int* result = allocateBits();
    addBits(aCompl, bCompl, result);
    int realResult = complementToInt(result);

    free(result);
    free(aCompl);
    free(bCompl);

    return realResult == a + b;
}

int randRange(int low, int high)
{
    assert(high > low && "high should be greater than low");
    return (rand() % (high - low)) + low; // NOLINT(cert-msc50-cpp)
}

int main(void)
{
    srand(time(0)); // NOLINT(cert-msc51-cpp)

    for (int i = 0; i < NUM_TESTS; i++) {
        int a = randRange(-10000, 10000);
        int b = randRange(-10000, 10000);
        assert(checkForTwoNumbers(a, b));
    }

    return 0;
}
