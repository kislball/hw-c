#include <stdhw.h>
#include <stdio.h>
#include <stdlib.h>

// Программа считает сумму всех чётных чисел Фибоначчи не превышающих миллиона.
int main()
{
    int prev = 1, current = 1;
    int sum = 0;

    while (current <= 1000000) {
	if (current % 2 == 0) sum += current;
	int next = current + prev;
	prev = current;
	current = next;
    }

    printf("Ответ: %d\n", sum);
    return 0;
}
