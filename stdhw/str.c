#include "str.h"
#include <stdlib.h>
#include <string.h>

char* trim(char* str)
{
    int spacesLeft = 0, spacesRight = 0;
    size_t len = strlen(str);

    for (int i = 0; i < len; i++) {
        if (isspace(str[i]))
            spacesLeft++;
        else
            break;
    }

    for (int i = len - 1; i >= 0; i--) {
        if (isspace(str[i]))
            spacesRight++;
        else
            break;
    }

    char* result = malloc(sizeof(char) * len + 1);

    strncpy(result, );	

    return result;
}
