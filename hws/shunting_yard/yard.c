#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdhw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN_PLUS (-1)
#define TOKEN_MINUS (-2)
#define TOKEN_MUL (-3)
#define TOKEN_DIV (-4)
#define TOKEN_OPEN (-5)

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

bool populateStacks(Stack* output, Stack* operators, const char* input)
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
                int opType = stackPeek(operators, &isSuccessful);
                if (!isSuccessful || getPriority(opType) < priority)
                    break;
                stackPop(operators, &isSuccessful);
                stackPush(output, opType);
            } while (isSuccessful);
            stackPush(operators, tokenToInt(cur));
        } else if (cur == '(') {
            stackPush(operators, TOKEN_OPEN);
        } else if (cur == ')') {
            bool isSuccessful = false;
            int intOp = stackPop(operators, &isSuccessful);
            if (!isSuccessful) {
                ok = false;
                break;
            }

            while (intOp != TOKEN_OPEN && isSuccessful) {
                stackPush(output, intOp);
                intOp = stackPop(operators, &isSuccessful);
                if (!isSuccessful) {
                    ok = false;
                }
            }
        }
    }

    bool isSuccessful = false;
    int op = stackPop(operators, &isSuccessful);
    while (isSuccessful) {
        if (op == TOKEN_OPEN) {
            ok = false;
            break;
        }
        stackPush(output, op);
        op = stackPop(operators, &isSuccessful);
    }

    return ok;
}

char* shuntingYard(char* input, Stack* output, Stack* operators)
{
    char* result = NULL;

    bool ok = populateStacks(output, operators, input);
    if (!ok)
        return NULL;

    result = calloc(output->size * 2, sizeof(char));
    if (result == NULL)
        return NULL;

    ok = true;
    int terminated = false;

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
    Stack operators = stackNew();

    char* result = shuntingYard(input, &output, &operators);
    stackDelete(&output);
    stackDelete(&operators);
    return result;
}
