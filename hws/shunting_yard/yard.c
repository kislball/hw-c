#include <assert.h>
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

bool populateStacks(Stack* output, Stack* operator, char* input)
{
    bool ok = true;

    for (int i = 0; input[i] != '\0' && ok; i++) {
        char cur = input[i];

        if (isspace(cur))
            continue;

        // В условии сказано про цифры, не числа
        if (isdigit(cur)) {
            stackPush(output, tokenToInt(cur));
        } else if (isOperator(cur)) {
            int priority = getPriority(tokenToInt(cur));
            bool isSuccessful = false;
            do {
                int opType = stackPeek(operator, &isSuccessful);
                if (!isSuccessful || getPriority(opType) < priority)
                    break;
                stackPop(operator, &isSuccessful);
                stackPush(output, opType);
            } while (isSuccessful);
            stackPush(operator, tokenToInt(cur));
        } else if (cur == '(') {
            stackPush(operator, TOKEN_OPEN);
        } else if (cur == ')') {
            bool isSuccessful = false;
            int intOp = stackPop(operator, &isSuccessful);
            if (!isSuccessful) {
                ok = false;
                break;
            }

            while (intOp != TOKEN_OPEN && isSuccessful) {
                stackPush(output, intOp);
                intOp = stackPop(operator, &isSuccessful);
                if (!isSuccessful) {
                    ok = false;
                }
            }
        }
    }

    bool isSuccessful = false;
    int op = stackPop(operator, &isSuccessful);
    while (isSuccessful) {
        if (op == TOKEN_OPEN) {
            ok = false;
            break;
        }
        stackPush(output, op);
        op = stackPop(operator, &isSuccessful);
    }

    return ok;
}

char* shuntingYard(char* input, Stack* output, Stack* operator)
{
    int inputLen = strlen(input);
    char* result = NULL;

    bool ok = populateStacks(output, operator, input);
    if (!ok)
        return NULL;

    result = calloc(output->size * 2, sizeof(char));
    if (result == NULL)
        return NULL;

    ok = true;
    int terminated = false;
    int i = output->size * 2 - 1;

    for (int i = output->size * 2 - 1; i > 0 && ok; i -= 2) {
        int v = stackPop(output, &ok);
        char tok = intToToken(v);
        char suffix = terminated ? ' ' : '\0';
        terminated = true;

        result[i] = suffix;
        result[i - 1] = tok;
    }

    return result;
}

char* shuntingYardAlloc(char* input)
{
    Stack output = stackNew();
    Stack operator = stackNew();

    char* result = shuntingYard(input, &output, &operator);
    stackDelete(&output);
    stackDelete(&operator);
    return result;
}
