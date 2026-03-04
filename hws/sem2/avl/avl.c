#include "destruct.h"
#include "list.h"
#include "map.h"
#include <stdlib.h>
#include <string.h>

typedef struct Map {
    Map* lesser;
    Map* greater;
    char* key;
    char* value;
    int balance;
} Map;

static Map* avlRotateLeft(Map* a)
{
    Map* b = a->greater;
    Map* c = b->lesser;

    b->lesser = a;
    a->greater = c;

    return b;
}

static Map* avlRotateRight(Map* a)
{
    Map* b = a->lesser;
    Map* c = b->greater;

    b->greater = a;
    a->lesser = c;
    return b;
}

static Map* avlBigRotateLeft(Map* a)
{
    a->greater = avlRotateRight(a->greater);
    return avlRotateLeft(a);
}

static Map* avlBigRotateRight(Map* a)
{
    a->lesser = avlRotateLeft(a->lesser);
    return avlRotateRight(a);
}

static Map* avlBalance(Map* m)
{
    if (m->balance == -1) {
        if (m->lesser && m->lesser->balance == -1) {
            m->balance = 0;
            m->lesser->balance = 0;
            return avlRotateRight(m);
        }

        if (m->lesser && m->lesser->balance == 0) {
            m->balance = -1;
            m->lesser->balance = 1;
            return avlRotateRight(m);
        }

        if (m->lesser && m->lesser->balance == 1 && m->lesser->greater) {
            if (m->lesser->greater->balance == 1) {
                m->balance = 0;
                m->lesser->balance = -1;
                m->lesser->greater->balance = 0;
            }

            else if (m->lesser->greater->balance == -1) {
                m->balance = 1;
                m->lesser->balance = 0;
                m->lesser->greater->balance = 0;
            }

            else if (m->lesser->greater->balance == 0) {
                m->balance = 0;
                m->lesser->balance = 0;
                m->lesser->greater->balance = 0;
            }

            return avlBigRotateRight(m);
        }
    }

    if (m->balance == 1) {
        if (m->greater && m->greater->balance == 1) {
            m->balance = 0;
            m->greater->balance = 0;
            return avlRotateLeft(m);
        }

        if (m->greater && m->greater->balance == 0) {
            m->balance = 1;
            m->greater->balance = -1;
            return avlRotateLeft(m);
        }

        if (m->greater && m->greater->balance == -1 && m->greater->lesser) {
            if (m->greater->lesser->balance == 1) {
                m->balance = -1;
                m->greater->balance = 0;
                m->greater->lesser->balance = 0;
            }

            else if (m->greater->lesser->balance == -1) {
                m->balance = 0;
                m->greater->balance = 1;
                m->greater->lesser->balance = 0;
            }

            else if (m->greater->lesser->balance == 0) {
                m->balance = 0;
                m->greater->balance = 0;
                m->greater->lesser->balance = 0;
            }

            return avlBigRotateLeft(m);
        }
    }

    return m;
}

void mapInsert(Map** m, char* key, char* value)
{
    Map* node = *m;
    if (node->key == nullptr) {
        node->key = strdup(key);
        node->value = strdup(value);
        node->balance = 0;
        return;
    }

    int cmpRes = strcmp(key, node->key);
    if (cmpRes == 0) {
        if (node->value)
            free(node->value);
        node->value = strdup(value);
        return;
    } else if (cmpRes < 0) {
        if (node->lesser) {
            mapInsert(&node->lesser, key, value);
        } else {
            node->lesser = mapNew();
            node->lesser->key = strdup(key);
            node->lesser->value = strdup(value);
        }
        node->balance--;
    } else {
        if (node->greater) {
            mapInsert(&node->greater, key, value);
        } else {
            node->greater = mapNew();
            node->greater->key = strdup(key);
            node->greater->value = strdup(value);
        }
        node->balance++;
    }

    if (node->balance == -2 || node->balance == 2) {
        *m = avlBalance(node);
    }
}

void mapDelete(Map** m, char* key)
{
    if (*m == nullptr)
        return;

    Map* node = *m;
    int cmpRes = strcmp(key, node->key);

    if (cmpRes < 0) {
        mapDelete(&node->lesser, key);
        node->balance++;
    } else if (cmpRes > 0) {
        mapDelete(&node->greater, key);
        node->balance--;
    } else {
        if (node->lesser == nullptr && node->greater == nullptr) {
            mapFree(&node);
            *m = nullptr;
            return;
        } else if (node->lesser == nullptr) {
            *m = node->greater;
            mapFree(&node);
        } else if (node->greater == nullptr) {
            *m = node->lesser;
            mapFree(&node);
        } else {
            Map** succ = &node->greater;
            while ((*succ)->lesser != nullptr) {
                succ = &(*succ)->lesser;
            }
            Map* s = *succ;
            free(node->key);
            free(node->value);
            node->key = strdup(s->key);
            node->value = strdup(s->value);
            mapDelete(&node->greater, s->key);
            node->balance--;
        }
    }

    if (*m != nullptr && ((*m)->balance == -2 || (*m)->balance == 2)) {
        *m = avlBalance(*m);
    }
}

Map* mapNew()
{
    Map* m = calloc(1, sizeof(*m));

    m->balance = 0;

    return m;
}

bool mapGet(Map* m, char* key, char** value)
{
    if (m == nullptr)
        return false;
    int res = strcmp(m->key, key);
    if (res == 0) {
        *value = strdup(m->value);
        return true;
    } else if (res > 0) {
        return mapGet(m->lesser, key, value);
    } else {
        return mapGet(m->greater, key, value);
    }
}

void mapFree(Map** m)
{
    if (*m == nullptr)
        return;

    if ((*m)->key)
        free((*m)->key);
    if ((*m)->value)
        free((*m)->value);

    mapFree(&(*m)->lesser);
    mapFree(&(*m)->greater);
    free(*m);
    *m = nullptr;
}

static void mapGetKeysRec(Map* m, LinkedList* list)
{
    if (m == nullptr)
        return;
    mapGetKeysRec(m->lesser, list);
    linkedListInsert(list, linkedListCount(list), strdup(m->key), true);
    mapGetKeysRec(m->greater, list);
}

LinkedList* mapGetKeys(Map* m)
{
    LinkedList* list = linkedListNewWithDestructor(free);
    mapGetKeysRec(m, list);
    return list;
}
