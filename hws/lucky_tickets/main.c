#include <stdio.h>
#include <strings.h>

int main()
{
    int sums[28] = { 0 };

    for (int a = 0; a <= 9; a++)
        for (int b = 0; b <= 9; b++)
            for (int c = 0; c <= 9; c++)
                sums[a + b + c] += 1;

    int n = 0;

    for (int i = 0; i < 28; i++) {
        n += sums[i] * sums[i];
    }

    printf("%d\n", n);
}
