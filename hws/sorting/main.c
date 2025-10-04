#include "sort.h"
#include <stdbool.h>
#include <stdhw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* readNumbers(int* len)
{
    char* initialStr = promptString("");
    // По условию не более ста чисел
    int* numbers = calloc(100, sizeof(int));
    *len = 0;

    char* p = initialStr;

    while (true)
    {
	char* end;
	long i = strtol(p, &end, 10);
	if (p == end) break;
	p = end;
	numbers[*len] = (int) i;
	(*len)++;
    }

    free(initialStr);
    return numbers;
}

int main()
{
    int n = 0;
    int* arr = readNumbers(&n);
    int* arrInitial = malloc(100 * sizeof(int));
    memset(arrInitial, 0, 100);
    for (int i = 0; i < n; i++) {
        arrInitial[i] = arr[i];
    }

    sort(arr, n);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    int changedPositions = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] != arrInitial[i]) {
            changedPositions++;
        }
    }

    free(arr);
    free(arrInitial);

    return changedPositions;
}
