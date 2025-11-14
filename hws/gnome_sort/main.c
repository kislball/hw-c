#include <stdhw.h>
#include <stdio.h>
#include <stdlib.h>

// Сортирует массив, начинающийся с элемента по адресу input, с длиной lеn по возрастанию.
void gnomeSort(int* input, int len)
{
    int i = 1;
    while (i < len) {
        if (i == 0)
            i++;
        if (input[i - 1] > input[i]) {
            int temp = input[i - 1];
            input[i - 1] = input[i];
            input[i] = temp;
            i--;
        } else {
            i++;
        }
    }
}

int main()
{
    int len = 0;
    int* input = promptIntArray("Введите массив чисел для сортировки", &len);

    gnomeSort(input, len);

    for (int j = 0; j < len; j++) {
        printf("%d ", input[j]);
    }
    printf("\n");

    free(input);
    return 0;
}
