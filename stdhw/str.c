#include "str.h"
#include <stdlib.h>
#include <string.h>

char* trimLeft(char* str) {
	size_t len = strlen(str);
	int shift = 0;
	for (int i = 0; i < len; i++) {
		if (str[i] == ' ') {
			shift++;
		} else {
			break;
		}
	}

	return str + shift;
}

void trimRight(char* str)
{
	size_t len = strlen(str);
	for (int i = len - 1; i >= 0; i--) {
		if (str[i] == ' ') {
			str[i] = '\0';
		} else {
			break;
		}
	}
}

char* trim(char *str)
{
	trimRight(str);
	return trimLeft(str);
}
