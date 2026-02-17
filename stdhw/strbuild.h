#pragma once

// Утилита для построения строки динамически
typedef struct StringBuilder StringBuilder;

// Создаёт новый инстанс структуры StringBuilder
StringBuilder* stringBuilderNew(void);
// Получение искомой строки, выделяется новая память, за управление которой отвечает вызывающая функция
char* stringBuild(StringBuilder*);
// Добавление к строке другой
void stringBuilderAppend(StringBuilder*, char*);
// Освобождение памяти, занимаемой инстансом структуры StringBuilder
void stringBuilderFree(StringBuilder**);
