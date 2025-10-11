#include <stdlib.h>
#include "yard.h"
#include <stdio.h>

int main(void)
{
    char* input = promptString("s=");
    char* result = shuntingYardAlloc(input);
    printf("%s\n", result == NULL ? "Incorrect input" : result);

    free(input);
    free(result);
    return 0;
}
