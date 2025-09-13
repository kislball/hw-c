#include <stdio.h>
#include <stdlib.h>

// Функция переворачивает массив длины len
void reverse(int *array, int len) {
	for (int i = 0; i <= len / 2 - 1; i++) {
		int temp = array[i];
		array[i] = array[len - i - 1];
		array[len - i - 1] = temp;
	}
}

void swap_ends(int *array, int n, int m) {
	reverse(array, n + m);
	reverse(array, n);
	reverse(array + n, m);
}

int prompt(char *data) {
	int ans = 0;
	printf("%s", data);
	scanf("%d", &ans);
	return ans;
}

int main() {
	const int n = prompt("Введите n: ");
	const int m = prompt("Введите m: ");
	const int len = m + n;

	int *array = malloc(len);

	for (int i = 0; i < len; i++) {
		printf("n = %d, ", i + 1);
		array[i] = prompt("введите элемент массива: ");
	}

	swap_ends(array, n, m);

	printf("\n");
	for (int i = 0; i < len; i++) {
		printf("%d ", array[i]);	
	}
	printf("\n");

	free(array);
	return 0;
}
