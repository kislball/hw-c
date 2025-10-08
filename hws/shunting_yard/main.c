#include <ctype.h>
#include <stdio.h>
#include <stdhw.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TOKEN_PLUS -1
#define TOKEN_MINUS -2
#define TOKEN_MUL -3
#define TOKEN_DIV -4
#define TOKEN_OPEN -5
#define TOKEN_CLOSE -6

bool isOperator(char op)
{
	switch (op) {
		case '+':
		case '-':
		case '*':
		case '/':
			return true;
		default:
			return false;
	}
}

int tokenToInt(char op)
{
	switch (op)
	{
		case '+': return TOKEN_PLUS;
		case '-': return TOKEN_MINUS;
		case '*': return TOKEN_MUL;
		case '/': return TOKEN_DIV;
		case '(': return TOKEN_OPEN;
		case ')': return TOKEN_CLOSE;
		default: return op - '0';
	}
}

char intToToken(int op) {
	switch (op) {
		case TOKEN_PLUS: return '+';
		case TOKEN_MINUS: return '-';
		case TOKEN_MUL: return '*';
		case TOKEN_DIV: return '/';
		case TOKEN_OPEN: return '(';
		case TOKEN_CLOSE: return ')';
		default: return (char) op + '0';
	}
}

int getPriority(int op)
{
	switch (op) {
		case TOKEN_PLUS:
		case TOKEN_MINUS:
			return 1;
		case TOKEN_MUL:
		case TOKEN_DIV:
			return 2;
		default: return -1;
	}
}

char* shuntingYard(char* input)
{
	Stack output = stackNew();
	Stack operator = stackNew();
	Stack reversed = stackNew();

	int inputLen = strlen(input);
	int outputMaxLen = 0;
	char* inputStart = input;
	char* inputEnd = input + inputLen;
	char* result = NULL;

	while (inputStart < inputEnd) {
		char cur = *inputStart;
		outputMaxLen += 3;

		// В условии сказано про цифры, не числа
		if (isdigit(cur)) {
			stackPush(&output, tokenToInt(cur));
		}
		else if (isOperator(cur)) {
			int priority = getPriority(tokenToInt(cur));
			bool has = false;
			do {
				int opType = stackPeek(&operator, &has);
				if (!has || getPriority(opType) < priority) break;
				stackPop(&operator, &has);
				stackPush(&output, opType);
			} while (has);
			stackPush(&operator, tokenToInt(cur));
		} else if (cur == '(') {
			stackPush(&operator, TOKEN_OPEN);
		} else if (cur == ')') {
			bool has = false;
			int intOp = stackPop(&operator, &has);
			if (!has) {
				goto over;
			}

			while (intOp != TOKEN_OPEN) {
				stackPush(&output, intOp);
				intOp = stackPop(&operator, &has);
				if (!has) goto over;
			}
		} else {
			outputMaxLen -= 1;
		} 
		inputStart ++;
	}

	bool has = false;
	int op = stackPop(&operator, &has);	
	while (has) {
		if (op == TOKEN_OPEN) return NULL;
		stackPush(&output, op);
		op = stackPop(&operator, &has);	
	}

	int v = 0;
	while ((v = stackPop(&output, &has)), has) {
		stackPush(&reversed, v);
	}
	
	int out = stackPop(&reversed, &has);
	result = malloc(sizeof(char) * outputMaxLen);
	if (result == NULL) goto over;
	memset(result, '\0', outputMaxLen);
	int i = 0;

	while (has) {
		char token = intToToken(out);
		result[i] = token;
		result[i + 1] = ' ';
		i += 2;

		out = stackPop(&reversed, &has);
	}
	result[i - 1] = '\0';

over:
	stackDelete(&output);
	stackDelete(&operator);
	stackDelete(&reversed);
	return result;
}

int main(void)
{
	char* input = promptString("s=");
	char* result = shuntingYard(input);
	printf("%s\n", result == NULL ? "Incorrect input" : result);

	free(input);
	free(result);
	return 0;
}

