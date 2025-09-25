#include "sort.h"
#include <stdhw.h>
#include <stdio.h>

int main()
{
    int len = 0;
    int* arr = promptIntArray("Введите числа", &len);
    sort(arr, len);

    for (int i = 0; i < len; i++)
        printf("%d\n", arr[i]);
}
