#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>

// tidy жалуется на то, что размер может быть заманипулирован scanf-ом,
// но в данном случае это, полагаю, не критично.
//NOLINTBEGIN clang-analyzer-optin.taint.TaintedAlloc
int* promptIntArray(char* promptString, int* len)
{
    printf("%s", promptString);
    *len = prompt(", введите количество элементов: ");

    int* data = malloc(sizeof(int) * *len);

    for (int i = 0; i < *len; i++) {
        printf("n=%d, ", i + 1);
        data[i] = prompt("введите элемент: ");
    }

    return data;
}

int prompt(char* data)
{
    int ans = 0;
    printf("%s", data);
    scanf("%d", &ans);
    return ans;
}

double promptDouble(char* data)
{
    double ans = 0;
    printf("%s", data);
    scanf("%lf", &ans);
    return ans;
}

char* promptString(char* promptString)
{
    size_t initialBufferSize = 16;
    printf("%s", promptString);

    char* buffer = malloc(sizeof(char) * initialBufferSize);
    size_t size = getline(&buffer, &initialBufferSize, stdin);
    // Removing newline character in the end
    buffer[size - 1] = '\0';

    return buffer;
}
//NOLINTEND
