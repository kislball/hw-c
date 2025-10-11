#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "yard.h"

int main(void) {
    const char* infix[] = {
        "3+4*2/(1-5)",
        "1+2",
        "1+2*3",
        "(1+2)*3",
        "4*(5+6)",
        "7+8/2-3",
        "9",
        "2*(3+4*(5-6))",
        "8/(4-2*2)",
        "((3))"
    };

    const char* expected[] = {
        "3 4 2 * 1 5 - / +",
        "1 2 +",
        "1 2 3 * +",
        "1 2 + 3 *",
        "4 5 6 + *",
        "7 8 2 / + 3 -",
        "9",
        "2 3 4 5 6 - * + *",
        "8 4 2 2 * - /",
        "3"
    };

    int failed = 0;
    size_t n = sizeof(infix)/sizeof(infix[0]);

    for (size_t i = 0; i < n; i++) {
        char* result = shuntingYardAlloc((char*)infix[i]);
        if (result == NULL) {
            printf("%s => получено: NULL, ожидалось: %s\n", infix[i], expected[i]);
            failed++;
        } else if (strcmp(result, expected[i]) != 0) {
            printf("%s => получено: '%s', ожидалось: '%s'\n", infix[i], result, expected[i]);
            failed++;
        } else {
            printf("%s => %s\n", infix[i], result);
        }
        free(result);
    }

    return failed;
}
