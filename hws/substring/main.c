#include <stdbool.h>
#include <stdhw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char* s = promptString("S: ");
    char* s1 = promptString("S1: ");

    int len_s = strlen(s);
    int len_s1 = strlen(s1);

    int n = 0;

    if (len_s == len_s1 && strcmp(s, s1) == 0) {
        n = 1;
    } else if (len_s > len_s1) {
        for (int i = 0; i <= len_s - len_s1; i++) {
            bool ok = true;
            for (int j = 0; j < len_s1; j++) {
                if (s1[j] != s[j + i]) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                n += 1;
            }
        }
    }

    printf("%d\n", n);
    free(s);
    free(s1);
    return 0;
}
