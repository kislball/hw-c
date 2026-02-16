#include "display.h"
#include "common.h"
#include "list.h"
#include "string.h"
#include <assert.h>
#include <stdbool.h>
#include <stdhw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    RowHeader,
    RowInner,
    RowFooter,
    RowOrphanHeader,
} RowType;

typedef enum {
    FontTop = 0,
    FontBottom = 1,
    FontInner = 2,
    FontInnerBold = 3,
    FontBottomBolder = 4,
} DataCellLineFontType;

static struct {
    char* begin;
    char* line;
    char* separator;
    char* end;
} dataCellLineFonts[] = {
    [FontTop] = { .begin = "╔", .line = "═", .separator = "╦", .end = "╗" },
    [FontInner] = { .begin = "╠", .line = "─", .separator = "┼", .end = "╣" },
    [FontInnerBold] = { .begin = "╠", .line = "═", .separator = "╬", .end = "╣" },
    [FontBottom] = { .begin = "╚", .line = "═", .separator = "╧", .end = "╝" },
    [FontBottomBolder] = { .begin = "╚", .line = "═", .separator = "╩", .end = "╝" },
};

static int getIntegerLength(int number)
{
    int n = number >= 0 ? 1 : 2;
    int x = abs(number);
    while (x >= 10) {
        x /= 10;
        n++;
    }

    return n;
}

static int dataCellGetMinLen(DataCell cell)
{
    switch (cell.type) {
    case DataCellString:
	    dieIfNot(cell.string != NULL, "String must not be NULL");
        return (int)strlen(cell.string);
    case DataCellInteger:
        return getIntegerLength(cell.integer);
    case DataCellFloating: {
        char buffer[64];
        snprintf(buffer, sizeof(buffer), "%.6f", cell.floating);
        bool hasDot = strchr(buffer, '.') != NULL;
        int bufLen = (int)strlen(buffer);

        int trailingZeroes = 0;

        if (hasDot) {
            for (char* b = buffer + bufLen - 1; b >= buffer; b--) {
                if (*b == '0' || *b == '.')
                    trailingZeroes++;
                else
                    break;
            }
        }

        return bufLen - trailingZeroes;
    }
    }
}

static char* dataCellPrint(DataCell cell)
{
    switch (cell.type) {
    case DataCellString:
        return strdup(cell.string);
    case DataCellInteger: {
        char* buffer = calloc(32, sizeof(char));
        dieIfNot(buffer != NULL, "Failed to allocate buffer for printing data cell");
        snprintf(buffer, 32, "%d", cell.integer);

        return buffer;
    }
    case DataCellFloating: {
        char* buffer = calloc(32, sizeof(char));
        dieIfNot(buffer != NULL, "Failed to allocate buffer for printing data cell");
        snprintf(buffer, 32, "%.6f", cell.floating);

        int len = dataCellGetMinLen(cell);
        buffer[len] = '\0';

        return buffer;
    }
    }
}

static void dataCellDrawLine(DataCellLineFontType font, StringBuilder* row, LinkedList* cells, LinkedList* colSizes)
{
    int totalColumns = linkedListCount(cells);
    stringBuilderAppend(row, dataCellLineFonts[font].begin);

    for (int i = 0; i < totalColumns; i++) {
        int sizeIdx = i % linkedListCount(colSizes);
        int* size;
        linkedListGet(colSizes, sizeIdx, (void**)&size);

        for (int j = 0; j < (*size) + 2; j++) {
            stringBuilderAppend(row, dataCellLineFonts[font].line);
        }
        stringBuilderAppend(row, i == totalColumns - 1 ? dataCellLineFonts[font].end : dataCellLineFonts[font].separator);
    }
    stringBuilderAppend(row, "\n");
}

static char* dataCellRenderRow(RowType type, LinkedList* cells, LinkedList* colSizes)
{
    StringBuilder* row = stringBuilderNew();
    int totalColumns = linkedListCount(cells);

    if (type == RowHeader || type == RowOrphanHeader) {
        dataCellDrawLine(FontTop, row, cells, colSizes);
    }

    stringBuilderAppend(row, "║");
    LinkedListIterator* it = linkedListIteratorNew(cells);
    int i = 0;
    for (DataCell* cell = NULL; linkedListIteratorNext(it, (void**)&cell);) {
        char* (*padder)(char*, size_t, char) = cell->type == DataCellString ? &padRight : &padLeft;

        int sizeIdx = i % linkedListCount(colSizes);
        int* size;
        linkedListGet(colSizes, sizeIdx, (void**)&size);

        stringBuilderAppend(row, " ");
        char* formatted = dataCellPrint(*cell);
        char* padded = padder(formatted, *size, ' ');
        stringBuilderAppend(row, padded);
        free(formatted);
        free(padded);

        if (i == totalColumns - 1 || type == RowHeader || type == RowOrphanHeader)
            stringBuilderAppend(row, " ║");
        else
            stringBuilderAppend(row, " │");

        i++;
    }
    stringBuilderAppend(row, "\n");

    linkedListIteratorFree(&it);

    switch (type) {
    case RowFooter:
        dataCellDrawLine(FontBottom, row, cells, colSizes);
        break;
    case RowOrphanHeader:
        dataCellDrawLine(FontBottomBolder, row, cells, colSizes);
        break;
    case RowHeader:
        dataCellDrawLine(FontInnerBold, row, cells, colSizes);
        break;
    case RowInner:
        dataCellDrawLine(FontInner, row, cells, colSizes);
        break;
    }

    char* final = stringBuild(row);
    stringBuilderFree(&row);
    return final;
}

char* dataCellRenderTable(LinkedList* cells, int width, int height)
{
    if (linkedListCount(cells) != width * height) {
        dieIfNot(false, "Incorrect input data");
        return NULL;
    }
    LinkedList* colSizes = linkedListNewWithDestructor(free);
    StringBuilder* builder = stringBuilderNew();

#define GET_XY(x, y) ((y) * width + (x))

    for (int i = 0; i < width; i++) {
        int* widest = calloc(1, sizeof(int));
        for (int j = 0; j < height; j++) {
            DataCell* cell = NULL;
            bool ok = linkedListGet(cells, GET_XY(i, j), (void**)&cell);
            dieIfNot(ok, "unreachable, bug");
            int w = dataCellGetMinLen(*cell);
            if (w > *widest)
                *widest = w;
        }
        linkedListInsert(colSizes, linkedListCount(colSizes), widest, true);
    }

    for (int j = 0; j < height; j++) {
        LinkedList* row = linkedListNew();
        for (int i = 0; i < width; i++) {
            DataCell* cell = NULL;
            bool ok = linkedListGet(cells, GET_XY(i, j), (void**)&cell);
            dieIfNot(ok, "unreachable, bug");
            linkedListInsert(row, linkedListCount(row), cell, true);
        }

        RowType type = RowInner;
        if (height == 1)
            type = RowOrphanHeader;
        else if (j == 0)
            type = RowHeader;
        else if (j == height - 1)
            type = RowFooter;

        stringBuilderAppend(builder, dataCellRenderRow(type, row, colSizes));

        linkedListFree(&row);
    }

    linkedListFree(&colSizes);
    char* res = stringBuild(builder);
    stringBuilderFree(&builder);

    return res;
}
