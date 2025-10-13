#include <ctype.h>
#include <stdhw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isPalindrome(char* input)
{
    int len = strlen(input);
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

int main()
{
    char* input = promptString("Введите строку: ");

    printf("%s\n", isPalindrome(input) ? "YES" : "NO");
    free(input);
    return 0;
}
