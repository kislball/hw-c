#include <stdhw.h>
#include <stdio.h>

int main()
{
    LinkedList list = linkedListNew();
    bool isRunning = true;

    while (isRunning) {
        int op = prompt("Введите номер операции(0 - выход, 1 - добавление элемента, 2 - удалить значение, 3 - печать списка): ");
        if (op < 0 || op > 3) {
            printf("Неизвестная операция\n");
            continue;
        }

        switch (op) {
        case 0:
            isRunning = false;
            break;
        case 1: {
            int value = prompt("Введите элемент: ");
            int index = 0;
            LINKED_LIST_FOREACH(&list, node)
            {
                if (node->value <= value)
                    index++;
                else
                    break;
            }

            bool ok = linkedListInsert(&list, index, value);
            printf("%s\n", ok ? "Элемент встроен в список" : "Неправильный индекс");

            break;
        }
        case 2: {
            int len = linkedListCount(&list);
            printf("Текущая длина списка: %d, ", len);
            int index = prompt("введите номер элемента для удаления: ");
            bool res = linkedListRemove(&list, index);
            printf("%s\n", res ? "Элемент удалён!" : "Неправильный индекс");
            break;
        }
        case 3:
            linkedListPrintStdout(&list);
            printf("\n");
            break;
        }
    }

    linkedListDelete(&list);
    return 0;
}
