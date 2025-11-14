#include <stdbool.h>
#include <stdhw.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char* input = promptString("S=");
    int n = 0;
    bool ok = true;

    size_t len = strlen(input);
    for (int i = 0; i < len; i++) {
        if (input[i] == '(') {
            n += 1;
        } else if (input[i] == ')') {
            n -= 1;
        }

        if (n < 0) {
            ok = false;
            break;
        }
    }

    if (ok && n == 0) {
        printf("CORRECT\n");
    } else {
        printf("INCORRECT\n");
    }

    return 0;
}
