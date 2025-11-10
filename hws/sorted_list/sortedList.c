#include "sortedList.h"
#include <assert.h>
#include <stdlib.h>

int sortedLinkedListInsert(LinkedList* list, int value)
{
    int index = 0;
    LINKED_LIST_FOREACH(list, node)
    {
	if (node->value <= value)
	    index++;
	else
	    break;
    }

    bool ok = linkedListInsert(list, index, value);
    assert(ok);

    return index;
}
