#include "list.h"
#include <assert.h>
#include <stdhw.h>
#include <stdio.h>

int main()
{
    LinkedList* list = linkedListNew();
    assert(linkedListCount(list) == 0 && "List should have length zero");

    linkedListInsert(list, 0, 10);
    linkedListInsert(list, 0, 20);
    linkedListInsert(list, 2, 30);

    int v = 0;
    bool res = linkedListGet(list, 0, &v);
    assert(res && "Insert on zero index is successful");
    assert(v == 20 && "Elements are inserted in correct order");

    linkedListGet(list, 1, &v);
    assert(v == 10 && "Elements are inserted in correct order");

    res = linkedListGet(list, 2, &v);
    assert(res && "Insert on non-zero index is successful");
    assert(v == 30 && "Elements are inserted in the correct order");

    assert(linkedListCount(list) == 3 && "Elements in a list are correctly counted");
    assert(linkedListRemove(list, 1) && "Removal is successful");
    linkedListGet(list, 0, &v);
    assert(v == 20 && "Elements are correctly removed");
    linkedListGet(list, 1, &v);
    assert(v == 30 && "Elements are correctly removed");
    assert(linkedListCount(list) == 2 && "Elements are correctly removed");

    linkedListPrintStdout(list);

    linkedListDelete(list);
    assert(linkedListCount(list) == 0 && "List is properly deleted");
    linkedListFree(&list);

    return 0;
}
