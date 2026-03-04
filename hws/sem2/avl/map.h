#pragma once

// АДТ ассоциативный массив
typedef struct Map Map;

// Инициализирует Map
Map* mapNew();
bool mapGet(Map* m, char* key, char** value);
void mapFree(Map**);
void mapInsert(Map** m, char* key, char* value);
void mapDelete(Map** m, char* key);
