#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>

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

char* promptString(char* promptString)
{
    size_t initial_buffer_size = 16;
    printf("%s", promptString);

    char* buffer = malloc(sizeof(char) * initial_buffer_size);
    int size = getline(&buffer, &initial_buffer_size, stdin);
    // Removing newline character in the end
    buffer[size - 1] = '\0';

    return buffer;
}
