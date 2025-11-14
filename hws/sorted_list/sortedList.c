#include "sortedList.h"
#include <assert.h>
#include <stdhw.h>
#include <stdlib.h>

int sortedLinkedListInsert(LinkedList* list, int value)
{
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
    assert(ok);

    linkedListIteratorFree(&it);
    return index;
}
