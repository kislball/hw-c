#include <stdhw.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_FIBONACCI 35

int main()
{
    int* fib = calloc(MAX_FIBONACCI, sizeof(int));
    fib[0] = 1;
    fib[1] = 1;

    for (int i = 2; i < MAX_FIBONACCI; i++)
        fib[i] = fib[i - 1] + fib[i - 2];

    int sum = 0;
    for (int i = 0; i < MAX_FIBONACCI; i += 1) {
        if (fib[i] <= 1000000 && fib[i] % 2 == 0)
            sum += fib[i];
    }

    printf("Ответ: %d\n", sum);
    free(fib);
    return 0;
}
