#pragma once
#include "list.h"
#include <stdio.h>

// АДТ ассоциативный массив
typedef struct Map Map;

// Инициализирует Map
Map* mapNew();
bool mapGet(Map* m, char* key, char** value);
void mapFree(Map**);
void mapInsert(Map** m, char* key, char* value);
void mapDelete(Map** m, char* key);
LinkedList* mapGetKeys(Map* m);

Map* mapImport(FILE*);
void mapExport(Map*, FILE*);
