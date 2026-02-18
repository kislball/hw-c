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

char* prettyCsv(char*);
