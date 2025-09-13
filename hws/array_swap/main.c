#include <stdio.h>
#include <stdlib.h>

void reverse(int* array, int len)
{
    for (int i = 0; i <= len / 2 - 1; i++) {
        int temp = array[i];
        array[i] = array[len - i - 1];
        array[len - i - 1] = temp;
    }
}

void swapEnds(int* array, int n, int m)
{
    reverse(array, n + m);
    reverse(array, n);
    reverse(array + n, m);
}

int prompt(char* data)
{
    int ans = 0;
    printf("%s", data);
    scanf("%d", &ans);
    return ans;
}

int main(void)
{
    int n = prompt("Введите n: ");
    int m = prompt("Введите m: ");
    int len = m + n;

    int* array = malloc(len);

    for (int i = 0; i < len; i++) {
        printf("i = %d, ", i + 1);
        array[i] = prompt("введите элемент массива: ");
    }

    swapEnds(array, n, m);

    printf("\n");
    for (int i = 0; i < len; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    return 0;
}
