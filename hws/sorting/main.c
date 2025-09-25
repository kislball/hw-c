#include "sort.h"
#include <stdbool.h>
#include <stdhw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* readNumbers(int* len)
{
    char* initialStr = promptString("");
    char* str = trim(initialStr);
    int inputLen = strlen(str);
    int totalNumbers = 1;

    for (int i = 0; i < inputLen - 1; i++) {
        if (str[i] == ' ' && str[i + 1] >= '0' && str[i + 1] <= '9') {
            totalNumbers += 1;
        }
    }

    int* numbers = malloc(sizeof(int) * totalNumbers);
    int curNumber = 0;
    int curNumberIdx = 0;

    for (int i = 0; i < inputLen; i++) {
        if (str[i] == ' ' || str[i] == '\n') {
            numbers[curNumberIdx] = curNumber;
            curNumber = 0;
            curNumberIdx++;
        } else if ('0' <= str[i] && str[i] <= '9') {
            curNumber *= 10;
            curNumber += (int)str[i] - '0';
        }
    }

    numbers[curNumberIdx] = curNumber;
    *len = totalNumbers;
    free(initialStr);
    return numbers;
}

int main()
{
    int n = 0;
    int* arr = readNumbers(&n);
    int* arrInitial = malloc(100 * sizeof(int));
    for (int i = 0; i < n; i++) {
        arrInitial[i] = arr[i];
    }

    memset(arrInitial, 0, 100);
    sort(arr, n);

    for (int i = 0; i < n; i++)
        printf("%d\n", arr[i]);

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
