#include "destruct.h"
#include "die.h"
#include "list.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Map {
    LinkedList* list;
} Map;

typedef struct MapEntry {
    char* key;
    char* value;
} MapEntry;

void mapEntryFree(MapEntry* entry)
{
    free(entry->key);
    free(entry->value);
    free(entry);
}

Map* mapNew()
{
    Map* m = calloc(1, sizeof(*m));
    m->list = linkedListNewWithDestructor((Destructor)mapEntryFree);

    return m;
}

void mapDelete(Map** map, char* key)
{
    Map* m = *map;
    LinkedListIterator* it = linkedListIteratorNew(m->list);
    bool ok = false;
    int idx = 0;

    for (MapEntry* entry = nullptr; linkedListIteratorNext(it, (void**)&entry); idx++) {
        if (!strcmp(entry->key, key)) {
            ok = true;
            break;
        }
    }

    if (ok)
        linkedListRemove(m->list, idx, true);
}

void mapInsert(Map** map, char* key, char* value)
{
    Map* m = *map;
    LinkedListIterator* it = linkedListIteratorNew(m->list);
    bool ok = false;

    for (MapEntry* entry = nullptr; linkedListIteratorNext(it, (void**)&entry);) {
        if (!strcmp(entry->key, key)) {
            if (entry->value)
                free(entry->value);
            entry->value = strdup(value);
            ok = true;
            break;
        }
    }

    linkedListIteratorFree(&it);

    if (!ok) {
        MapEntry* entry = calloc(1, sizeof(*entry));
        entry->key = strdup(key);
        entry->value = strdup(value);
        dieIfNot(linkedListInsert(m->list, 0, entry, true), "Failed to insert");
    }
}

bool mapGet(Map* m, char* key, char** value)
{
    LinkedListIterator* it = linkedListIteratorNew(m->list);
    bool ok = false;

    for (MapEntry* entry = nullptr; linkedListIteratorNext(it, (void**)&entry);) {
        if (!strcmp(entry->key, key)) {
            *value = strdup(entry->value);
            ok = true;
            break;
        }
    }

    linkedListIteratorFree(&it);
    return ok;
}

void mapFree(Map** m)
{
    linkedListFree(&(*m)->list);
    free(*m);
    *m = nullptr;
}
