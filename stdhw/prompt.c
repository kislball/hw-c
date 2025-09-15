#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>

int* PromptIntArray(char* prompt, int* len)
{
    printf("%s", prompt);
    *len = Prompt(", введите количество элементов: ");

    int* data = malloc(sizeof(int) * *len);

    for (int i = 0; i < *len; i++) {
        printf("n=%d, ", i + 1);
        data[i] = Prompt("введите элемент: ");
    }

    return data;
}

int Prompt(char* data)
{
    int ans = 0;
    printf("%s", data);
    scanf("%d", &ans);
    return ans;
}
