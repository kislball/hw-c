#include "list.h"
#include <assert.h>
#include <stdhw.h>
#include <stdio.h>

void testReverse(void)
{
    LinkedList* list = linkedListNew();

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;

    linkedListInsert(list, 0, &a);
    linkedListInsert(list, 1, &b);
    linkedListInsert(list, 2, &c);
    linkedListInsert(list, 3, &d);

    LinkedList* reversed = linkedListReverse(list);
    assert(linkedListCount(reversed) == linkedListCount(list) && "Lists have the same length");

    int *value = 0;
    assert(linkedListGet(reversed, 0, (void**)&value) && *value == 4 && "List is properly reversed");
    assert(linkedListGet(reversed, 1, (void**)&value) && *value == 3 && "List is properly reversed");
    assert(linkedListGet(reversed, 2, (void**)&value) && *value == 2 && "List is properly reversed");
    assert(linkedListGet(reversed, 3, (void**)&value) && *value == 1 && "List is properly reversed");

    linkedListFree(&list);
    linkedListFree(&reversed);
    assert(list == NULL && reversed == NULL && "Pointers are NULL after free");
}

int main(void)
{
    LinkedList* list = linkedListNew();
    assert(linkedListCount(list) == 0 && "List should have length zero");
    int a = 10;
    int b = 20;
    int c = 30;

    linkedListInsert(list, 0, &a);
    linkedListInsert(list, 0, &b);
    linkedListInsert(list, 2, &c);
    assert(linkedListCount(list) == 3 && "Elements are correctly counted");

    void* v = 0;
    bool res = linkedListGet(list, 0, &v);
    assert(res && "Insert on zero index is successful");
    assert(*(int*)v == 20 && "Elements are inserted in correct order");

    linkedListGet(list, 1, &v);
    assert(*(int*)v == 10 && "Elements are inserted in correct order");

    res = linkedListGet(list, 2, &v);
    assert(res && "Insert on non-zero index is successful");
    assert(*(int*)v == 30 && "Elements are inserted in the correct order");

    assert(linkedListCount(list) == 3 && "Elements in a list are correctly counted");
    assert(linkedListRemove(list, 1) && "Removal is successful");
    assert(linkedListCount(list) == 2 && "Elements are correctly counted");
    linkedListGet(list, 0, &v);
    assert(*(int*)v == 20 && "Elements are correctly removed");
    linkedListGet(list, 1, &v);
    assert(*(int*)v == 30 && "Elements are correctly removed");
    assert(linkedListCount(list) == 2 && "Elements are correctly removed");

    linkedListPrintStdout(list);

    LinkedListIterator* it = linkedListIteratorNew(list);
    int count = 0;
    for (int* i = 0; linkedListIteratorNext(it, (void**)&i);) {
        printf("%d\n", *i);
        count++;
    }
    linkedListIteratorFree(&it);
    assert(linkedListCount(list) == count && "Iterator is executed for all elements");

    linkedListDelete(list);
    assert(linkedListCount(list) == 0 && "List is properly deleted");
    linkedListFree(&list);

    testReverse();

    return 0;
}
