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

char* PromptString(char* prompt)
{
    size_t initial_buffer_size = 16;
    printf("%s", prompt);

    char* buffer = malloc(sizeof(char) * initial_buffer_size);
    int size = getline(&buffer, &initial_buffer_size, stdin);
    // Removing newline character in the end
    buffer[size - 1] = '\0';

    return buffer;
}
