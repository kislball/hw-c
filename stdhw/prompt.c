#include "prompt.h"
#include <stdio.h>

int Prompt(char* data)
{
    int ans = 0;
    printf("%s", data);
    scanf("%d", &ans);
    return ans;
}
