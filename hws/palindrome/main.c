#include <ctype.h>
#include <stdhw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Проверяет явяляется ли переданная строка палиндромом.
// Игнорирует пробелы. Возвращает true или false.
bool isPalindrome(char* input)
{
    size_t len = strlen(input);
    char* left = input;
    char* right = input + len - 1;

    while (left <= right) {
        while (isspace(*left))
            left++;
        while (isspace(*right))
            right--;
        if (*left != *right)
            return false;
        left++;
        right--;
    }

    return true;
}

int main(void)
{
    char* input = promptString("Введите строку: ");

    printf("%s\n", isPalindrome(input) ? "YES" : "NO");
    free(input);
    return 0;
}
