#pragma once

#include "list.h"
#include <stdio.h>

// Структура, содержащая в себе данные CSV таблицы
typedef struct CSVTable CSVTable;

// Возвращает ссылку на внутренний массив DataCell
LinkedList* csvGetCellsView(CSVTable* table);
// Копирует внутренний массив DataCell и возвращает его
LinkedList* csvGetCells(CSVTable* table);
// Выделяет память под структуру CSVTable
CSVTable* csvNew(void);
// Возвращает количество столбцов CSV таблицы
int csvWidth(CSVTable*);
// Возвращает количество строк CSV таблицы
int csvHeight(CSVTable*);
// Освобождает память, занимаемую CSV таблицей
void csvFree(CSVTable** table);
// Парсинг новой строки и добавление соотв. ячеек
bool csvFeedLine(CSVTable* table, const char* line);
// Полностью считывает файл и записывает строки из него
bool csvFeedFile(CSVTable* table, FILE* file);
