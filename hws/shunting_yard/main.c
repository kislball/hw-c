#include <ctype.h>
#include <stdbool.h>
#include <stdhw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN_PLUS -1
#define TOKEN_MINUS -2
#define TOKEN_MUL -3
#define TOKEN_DIV -4
#define TOKEN_OPEN -5

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
    switch (op) {
    case '+':
        return TOKEN_PLUS;
    case '-':
        return TOKEN_MINUS;
    case '*':
        return TOKEN_MUL;
    case '/':
        return TOKEN_DIV;
    case '(':
        return TOKEN_OPEN;
    default:
        return op - '0';
    }
}

char intToToken(int op)
{
    switch (op) {
    case TOKEN_PLUS:
        return '+';
    case TOKEN_MINUS:
        return '-';
    case TOKEN_MUL:
        return '*';
    case TOKEN_DIV:
        return '/';
    case TOKEN_OPEN:
        return '(';
    default:
        return (char)op + '0';
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
    default:
        return -1;
    }
}

char* shuntingYard(char* input)
{
    Stack output = stackNew();
    Stack operator = stackNew();
    Stack reversed = stackNew();

    int inputLen = strlen(input);
    char* result = NULL;

    for (int i = 0; input[i] != '\0'; i++) {
        char cur = input[i];

        // В условии сказано про цифры, не числа
        if (isdigit(cur)) {
            stackPush(&output, tokenToInt(cur));
        } else if (isOperator(cur)) {
            int priority = getPriority(tokenToInt(cur));
            bool isSuccessful = false;
            do {
                int opType = stackPeek(&operator, &isSuccessful);
                if (!isSuccessful || getPriority(opType) < priority)
                    break;
                stackPop(&operator, &isSuccessful);
                stackPush(&output, opType);
            } while (isSuccessful);
            stackPush(&operator, tokenToInt(cur));
        } else if (cur == '(') {
            stackPush(&operator, TOKEN_OPEN);
        } else if (cur == ')') {
            bool isSuccessful = false;
            int intOp = stackPop(&operator, &isSuccessful);
            if (!isSuccessful) {
                goto over;
            }

            while (intOp != TOKEN_OPEN) {
                stackPush(&output, intOp);
                intOp = stackPop(&operator, &isSuccessful);
                if (!isSuccessful)
                    goto over;
            }
        } 
    }

    bool isSuccessful = false;
    int op = stackPop(&operator, &isSuccessful);
    while (isSuccessful) {
        if (op == TOKEN_OPEN)
            return NULL;
        stackPush(&output, op);
        op = stackPop(&operator, &isSuccessful);
    }

    int v = stackPop(&output, &isSuccessful);
    while (isSuccessful) {
        stackPush(&reversed, v);
	v = stackPop(&output, &isSuccessful);
    }

    int out = stackPop(&reversed, &isSuccessful);
    result = calloc(inputLen * 2, sizeof(char));
    if (result == NULL)
        goto over;
    int i = 0;

    while (isSuccessful) {
        char token = intToToken(out);
        result[i] = token;
        result[i + 1] = ' ';
        i += 2;

        out = stackPop(&reversed, &isSuccessful);
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
