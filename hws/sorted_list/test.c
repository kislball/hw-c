#include "list.h"
#include "sortedList.h"
#include <assert.h>
#include <stdhw.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TEST_STEPS 1000

int main(void)
{
    // Некоторые проверки касаемо rand были отключены, так как в данном случае
    // отсутствует необходимость в сильном рандоме.
    srand(time(NULL)); // NOLINT(cert-msc51-cpp)
    LinkedList* list = linkedListNew();

    for (int i = 0; i < TEST_STEPS; i++) {
        if (rand() % 10 == 0) { // NOLINT(cert-msc50-cpp)
            int len = linkedListCount(list);
            int targetIdx = rand() % len; // NOLINT(cert-msc50-cpp)
            linkedListRemove(list, targetIdx);
        } else {
            int val = rand(); // NOLINT(cert-msc50-cpp)
            sortedLinkedListInsert(list, val);
        }
    }

    int previousValue = 0;
    assert(linkedListGet(list, 0, &previousValue));

    LinkedListIterator* it = linkedListIteratorNew(list);
    int currentValue = 0;
    while (linkedListIteratorNext(it, &currentValue)) {
        assert(previousValue <= currentValue);
        previousValue = currentValue;
    }

    linkedListDelete(list);
    linkedListFree(&list);
    return 0;
}
