#include "stack.h"
#include <stdhw.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef enum {
	NotAParen = -1, // что угодно, но не нижеперечисленные символы
	RoundParen = 0, // ()
	SquareParen = 1, // []
	WaveyParen = 2, // {}
} ParenType;

bool isOpeningParen(char ch)
{
	return ch == '(' || ch == '[' || ch == '{'; 
}

bool isClosingParen(char ch)
{
	return ch == ')' || ch == ']' || ch == '}'; 
}

bool isParen(char ch)
{
	return isClosingParen(ch) || isOpeningParen(ch);
}

ParenType resolveParenType(char ch)
{
	switch (ch)
	{
		case '(':
		case ')':
			return RoundParen;
		case '[':
		case ']':
			return SquareParen;
		case '{':
		case '}':
			return WaveyParen;
		default:
			return NotAParen;
	}
}

bool checkParenBalance(char *input)
{
	size_t len = strlen(input);
	Stack parens = stackNew();

	for (int i = 0; i < len; i++) {
		char current = input[i];
		if (!isParen(current)) continue;
		ParenType type = resolveParenType(current);

		if (isOpeningParen(current)) {
			stackPush(&parens, (int) type);
		} else if (isClosingParen(current)) {
			bool has = false;
			ParenType onTop = stackPop(&parens, &has);
			if (!has || onTop != type) return false;
		}
	}

	bool has = false;
	stackPeek(&parens, &has);
	stackDelete(&parens);
	return !has;
}

int main(void)
{
	char* input = promptString("s=");
	bool ok = checkParenBalance(input);
	
	printf("%s\n", ok ? "YES" : "NO");
	return 0;
}
