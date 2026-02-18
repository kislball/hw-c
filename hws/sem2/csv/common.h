// Ячейка в CSV таблице
typedef struct {
    enum {
        DataCellInteger,
        DataCellString,
        DataCellFloating,
    } type;
    union {
        int integer;
        double floating;
        char* string;
    };
} DataCell;

// Форматирование CSV таблицы используя псевдографику
char* prettyCsv(char*);
