#pragma once

#include <stddef.h>

// Добавляет к source символы character слева(с начала), чтобы длина была не менее targetSize.
// Возвращаемая строка *всегда* выделяется в памяти за очистку этой памяти отвечает вызывающая функция.
char* padLeft(char* source, size_t targetSize, char character);
// Добавляет к source символы character справа(с конца), чтобы длина была не менее targetSize.
// Возвращаемая строка *всегда* выделяется в памяти за очистку этой памяти отвечает вызывающая функция.
char* padRight(char* source, size_t targetSize, char character);
