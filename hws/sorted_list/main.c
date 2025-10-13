#include <stdhw.h>
#include <stdio.h>

int main(void)
{
    LinkedList* list = linkedListNew();
    bool isRunning = true;

    while (isRunning) {
        int op = prompt("Введите номер операции(0 - выход, 1 - добавление элемента, 2 - удалить значение, 3 - печать списка): ");

        switch (op) {
        case 0:
            isRunning = false;
            break;
        case 1: {
            int value = prompt("Введите элемент: ");
            int index = 0;
            LinkedListIterator* it = linkedListIteratorNew(list);
            int nodeValue = 0;
            while (linkedListIteratorNext(it, &nodeValue)) {
                if (nodeValue <= value)
                    index++;
                else
                    break;
            }

            bool ok = linkedListInsert(list, index, value);
            printf("%s\n", ok ? "Элемент встроен в список" : "Неправильный индекс");
            linkedListIteratorFree(&it);

            break;
        }
        case 2: {
            int len = linkedListCount(list);
            printf("Текущая длина списка: %d, ", len);
            int index = prompt("введите номер элемента для удаления: ");
            bool res = linkedListRemove(list, index);
            printf("%s\n", res ? "Элемент удалён!" : "Неправильный индекс");
            break;
        }
        case 3:
            linkedListPrintStdout(list);
            printf("\n");
            break;
        default:
            printf("Неизвестная операция\n");
            break;
        }
    }

    linkedListDelete(list);
    linkedListFree(&list);
    return 0;
}
