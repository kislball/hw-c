#include "map.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    Map* m = mapNew();

    mapInsert(&m, "a", "b");
    mapInsert(&m, "c", "d");
    mapInsert(&m, "e", "f");

    char* value;
    assert(mapGet(m, "a", &value) && !strcmp(value, "b") && "Values have been inserted correctly");
    free(value);
    assert(mapGet(m, "c", &value) && !strcmp(value, "d") && "Values have been inserted correctly");
    free(value);
    assert(mapGet(m, "e", &value) && !strcmp(value, "f") && "Values have been inserted correctly");
    free(value);

    mapInsert(&m, "e", "xd");
    assert(mapGet(m, "e", &value) && !strcmp(value, "xd") && "Values have been inserted correctly");
    free(value);

    assert(!mapGet(m, "t", &value) && "Value not present");
    mapDelete(&m, "e");
    assert(!mapGet(m, "e", &value) && "Value not present after deletion");

    mapFree(&m);
    assert(m == nullptr && "Map has been freed and pointer has been nulled");
    return 0;
}
