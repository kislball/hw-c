#include <stdhw.h>
#include <stdio.h>
#include <stdlib.h>

// Воин в ряду.
typedef struct Warrior {
    struct Warrior* next;
    int ord;
} Warrior;

// Определяет номер выжившего воина из n бойцов, которые убивают каждого m-ого.
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

        // clang-tidy жалуется на use-after-free(temp),
        // однако это не так, ведь так как current более не используется, так как единственный указатель на него
        // находится в before->next и при этом стирается до освобождения.
        before->next = current->next; // NOLINT
        Warrior* temp = current;
        current = current->next;
        free(temp);
    }

    int survivor = current->ord;
    free(current);
    return survivor;
}

int main(void)
{
    int n = prompt("n=");
    int m = prompt("m=");
    printf("%d\n", warriors(n, m));
    return 0;
}
