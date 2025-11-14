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
    srand(time(NULL));
    LinkedList* list = linkedListNew();

    for (int i = 0; i < TEST_STEPS; i++) {
        if (rand() % 10 == 0) {
            int len = linkedListCount(list);
            int target_idx = rand() % len;
            linkedListRemove(list, target_idx);
        } else {
            int val = rand();
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
