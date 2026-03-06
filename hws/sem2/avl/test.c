#include "map.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* shift(char* s, char n)
{
    char* res = strdup(s);
    unsigned int size = strlen(res);

    for (unsigned i = 0; i < size; i++) {
        res[i] += n; // NOLINT(cppcoreguidelines-narrowing-conversions)
    }

    return res;
}

void fuzzy()
{
    Map* m = mapNew();

    for (int i = 0; i <= 10000; i++) {
        char buf[32] = { };
        sprintf(buf, "%d", i);

        for (int j = 0; j < (i % 10); j++) {
            mapInsert(&m, buf, shift(buf, i % 3)); // NOLINT
            char* value;
            assert(mapGet(m, buf, &value) && !strcmp(value, shift(buf, i % 3)));
            if (j % 2 == 0) {
                mapDelete(&m, buf);
                assert(!mapGet(m, buf, &value));
            }
        }
    }

    mapFree(&m);
}

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
    fuzzy();
    return 0;
}
