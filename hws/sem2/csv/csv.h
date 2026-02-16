#pragma once

#include "list.h"
#include <stdio.h>

typedef struct CSVTable CSVTable;

LinkedList* csvGetCellsView(CSVTable* table);
LinkedList* csvGetCells(CSVTable* table);
CSVTable* csvNew(void);
int csvWidth(CSVTable*);
int csvHeight(CSVTable*);
void csvFree(CSVTable** table);
bool csvFeedLine(CSVTable* table, const char* line);
bool csvFeedFile(CSVTable* table, FILE* file);
