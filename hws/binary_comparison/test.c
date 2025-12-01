#include "compare.h"
#include <assert.h>

int main(void)
{
    for (int i = 0; i <= 10000; i++) {
        for (int j = 0; j <= 10000; j++) {
            ComparisonResult result = compare(i, j);
            if (i == j)
                assert(result == CompEqual && "a == b");
            if (i > j)
                assert(result == CompGreater && "a > b");
            if (i < j)
                assert(result == CompLess && "a < b");
        }
    }

    return 0;
}
