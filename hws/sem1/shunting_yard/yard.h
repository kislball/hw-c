#include <stdbool.h>
#include <stdhw.h>

// Заполняет стеки в соответствии с алгоритмом сортировочной станции
bool populateStacks(Stack* output, Stack* operator, char * input);

// Алгоритм сортировочной станции. На вход принимает входные данные, а так же три стека.
// Подразумевается, что память, на которую указывает возвращаемый указатель, очищается пользователем.
char* shuntingYard(char* input, Stack* output, Stack* operator);

// То же самое, что и shuntingYard, но самостоятельно выделяет и очищает память за исключением
// выходных данных.
char* shuntingYardAlloc(char* input);
