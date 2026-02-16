#include "csv.h"
#include "common.h"
#include "die.h"
#include "list.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT_TABLE_NOT_NULL(table) dieIfNot((table) != NULL, "Table must not be null");

typedef struct CSVTable {
    LinkedList* cells;
    int width;
    int height;
} CSVTable;

void csvFreeDataCell(void* cell)
{
    DataCell* c = cell;
    if (c->type == DataCellString)
        free(c->string);
    free(cell);
}

LinkedList* csvGetCellsView(CSVTable* table)
{
    ASSERT_TABLE_NOT_NULL(table);
    LinkedList* cells = linkedListNewWithDestructor(csvFreeDataCell);
    LinkedListIterator* it = linkedListIteratorNew(table->cells);

    for (DataCell* cell = NULL; linkedListIteratorNext(it, (void**)&cell);) {
        DataCell* newCell = calloc(1, sizeof(*newCell));
        dieIfNot(newCell != NULL, "Failed to allocate buffer");
        *newCell = *cell;
        if (newCell->type == DataCellString)
            newCell->string = strdup(newCell->string);
        linkedListInsert(cells, linkedListCount(cells), newCell, false);
    }

    linkedListIteratorFree(&it);

    return cells;
}

int csvHeight(CSVTable* table)
{
    return table->height;
}

int csvWidth(CSVTable* table)
{
    return table->width;
}

LinkedList* csvGetCells(CSVTable* table)
{
    return table->cells;
}

CSVTable* csvNew(void)
{
    CSVTable* table = calloc(1, sizeof(*table));
    dieIfNot(table != NULL, "Failed to allocate memory for a CSV table");
    LinkedList* cells = linkedListNewWithDestructor(csvFreeDataCell);
    table->cells = cells;
    table->width = 0;
    table->height = 0;

    return table;
}

void csvFree(CSVTable** table)
{
    ASSERT_TABLE_NOT_NULL(table);
    ASSERT_TABLE_NOT_NULL(*table);
    linkedListFree(&(*table)->cells);
    free(*table);
    *table = NULL;
}

DataCell csvSegmentIntoCell(char* segment)
{
    bool isNumeric = *segment == '-' || isdigit(*segment);
    bool hasDot = strchr(segment, '.') != NULL;
    for (char* cur = segment; *cur != '\0' && isNumeric; cur++) {
        if (!isdigit(*cur) && *cur != '.' && *cur != '-')
            isNumeric = false;
    }

    if (isNumeric) {
        DataCell cell;
        if (hasDot) {
            cell.type = DataCellFloating;
            cell.floating = atof(segment);
        } else {
            cell.type = DataCellInteger;
            cell.integer = atoi(segment);
        }
        return cell;
    } else {
        DataCell cell = { .type = DataCellString, .string = segment };
        return cell;
    }
}

bool csvFeedLine(CSVTable* table, const char* line)
{
    LinkedList* rawSegments = linkedListNewWithDestructor(NULL);
    size_t len = strlen(line);

    char* buffer = calloc(len, sizeof(char));
    dieIfNot(buffer != NULL, "Failed to allocate buffer");
    char* bufferBegin = buffer;

    for (const char* cur = line; cur < line + len; cur++) {
        if (*cur == ',') {
            linkedListInsert(rawSegments, linkedListCount(rawSegments), buffer, false);
            buffer = calloc(len, sizeof(char));
            dieIfNot(buffer != NULL, "Failed to allocate buffer");
            bufferBegin = buffer;
        } else if (*cur == '\n') {
            break;
        } else {
            *bufferBegin = *cur;
            bufferBegin++;
        }
    }
    if (*buffer != '\0') 
            linkedListInsert(rawSegments, linkedListCount(rawSegments), buffer, false);

    if (table->width == 0)
        table->width = linkedListCount(rawSegments);
    if (linkedListCount(rawSegments) != table->width) {
        linkedListFree(&rawSegments);
        return false;
    }
    table->height++;

    LinkedListIterator* it = linkedListIteratorNew(rawSegments);

    for (char* segment = NULL; linkedListIteratorNext(it, (void**)&segment);) {
        DataCell* cell = calloc(1, sizeof(*cell));
        dieIfNot(cell != NULL, "Failed to allocate cell");
        *cell = csvSegmentIntoCell(segment);
        linkedListInsert(table->cells, linkedListCount(table->cells), cell, false);
    }

    linkedListIteratorFree(&it);
    linkedListFree(&rawSegments);

    return true;
}

bool csvFeedFile(CSVTable* table, FILE* file)
{
    char buffer[512];
    memset(buffer, 0, 512);

    while (!feof(file)) {
        fgets(buffer, 512, file);
        bool ok = csvFeedLine(table, buffer);
        if (!ok)
            return false;

        memset(buffer, 0, 512);
    }

    return true;
}
