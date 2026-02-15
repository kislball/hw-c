#include "display.h"
#include "common.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    DataCell row[] = {
        { .type = DataCellString, .string = "Hello" },
        { .type = DataCellInteger, .integer = 25 },
        { .type = DataCellFloating, .floating = 472.1f },
        { .type = DataCellString, .string = "Hello" },
        { .type = DataCellInteger, .integer = 25 },
        { .type = DataCellFloating, .floating = 472.1f },
        { .type = DataCellString, .string = "Hello" },
        { .type = DataCellInteger, .integer = 25 },
        { .type = DataCellFloating, .floating = 472.1f },
        { .type = DataCellString, .string = "Hello" },
        { .type = DataCellInteger, .integer = 25 },
        { .type = DataCellFloating, .floating = 472.1f },
        { .type = DataCellString, .string = "Hello" },
        { .type = DataCellInteger, .integer = 25 },
        { .type = DataCellFloating, .floating = 472.1f },
        { .type = DataCellFloating, .floating = 472.1f },
    };
    LinkedList* cells = linkedListNew();
    for (int i = 0; i < 16; i++)
        linkedListInsert(cells, 0, row + i, false);
    printf("%s", dataCellRenderTable(cells, 4, 4));

    return 0;
}
