#include <stdhw.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Warrior {
    struct Warrior* next;
    int ord;
} Warrior;

int warriors(int n, int m)
{
    Warrior* first = malloc(sizeof(Warrior));
    first->next = NULL;
    first->ord = 1;
    Warrior* last = first;

    for (int i = 2; i <= n; i++) {
        Warrior* next = malloc(sizeof(Warrior));
        last->next = next;
        next->next = NULL;
        next->ord = last->ord + 1;
        last = next;
    }

    last->next = first;

    Warrior* current = first;
    Warrior* before = last;

    while (current->next != current) {
        for (int i = 1; i < m; i++) {
            before = current;
            current = before->next;
        }

        before->next = current->next;
        Warrior* temp = current;
        current = current->next;
        free(temp);
    }

    int survivor = current->ord;
    free(current);
    return survivor;
}

int main()
{
    int n = prompt("n=");
    int m = prompt("m=");
    printf("%d\n", warriors(n, m));
    return 0;
}
