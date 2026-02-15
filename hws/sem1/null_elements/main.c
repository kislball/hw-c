#include <stdhw.h>
#include <stdio.h>

int main(void)
{
    int len = 0;
    int n = 0;
    int* elements = promptIntArray("Необходим массив", &len);

    for (int i = 0; i < len; i++) {
        if (elements[i] == 0) {
            n += 1;
        }
    }

    printf("Ответ: %d\n", n);

    return 0;
}
