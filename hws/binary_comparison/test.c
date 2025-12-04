#include "compare.h"
#include <assert.h>

int main(void)
{
    for (int i = 0; i <= 1000; i++) {
        for (int j = 0; j <= 1000; j++) {
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
