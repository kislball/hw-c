#include "list.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>

void mapExport(Map* m, FILE* f)
{
    LinkedList* keys = mapGetKeys(m);
    LinkedListIterator* it = linkedListIteratorNew(keys);

    for (char* key = nullptr; linkedListIteratorNext(it, (void**)&key);) {
        char* value = nullptr;

        mapGet(m, key, &value);
        fprintf(f, "%s:%s\n", key, value);
        free(value);
    }

    linkedListFree(&keys);
    linkedListIteratorFree(&it);
}

Map* mapImport(FILE* f)
{
    Map* m = mapNew();
    char keyBuffer[512] = { };
    char valueBuffer[512] = { };

    while (fscanf(f, "%511[^:]:%511[^\n]\n", keyBuffer, valueBuffer) == 2) {
        mapInsert(&m, keyBuffer, valueBuffer);
    }

    return m;
}
