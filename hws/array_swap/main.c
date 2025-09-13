#include <stdio.h>
#include <stdlib.h>

void Reverse(int* array, int len)
{
    for (int i = 0; i <= len / 2 - 1; i++) {
        int temp = array[i];
        array[i] = array[len - i - 1];
        array[len - i - 1] = temp;
    }
}

void SwapEnds(int* array, int n, int m)
{
    Reverse(array, n + m);
    Reverse(array, n);
    Reverse(array + n, m);
}

int Prompt(char* data)
{
    int ans = 0;
    printf("%s", data);
    scanf("%d", &ans);
    return ans;
}

int main(void)
{
    int n = Prompt("Введите n: ");
    int m = Prompt("Введите m: ");
    int len = m + n;

    int* array = malloc(len);

    for (int i = 0; i < len; i++) {
        printf("i = %d, ", i + 1);
        array[i] = Prompt("введите элемент массива: ");
    }

    SwapEnds(array, n, m);

    printf("\n");
    for (int i = 0; i < len; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    return 0;
}
