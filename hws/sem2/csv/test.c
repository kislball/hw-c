#include "common.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* input;
    char* expected;
} TestCase;

void assertTestCase(TestCase tCase)
{
    char* out = prettyCsv(tCase.input);
    printf("Test case.\nInput:\n%s\nOutput:\n%s\nExpected:\n%s\n", tCase.input, tCase.expected, out);
    assert(!strcmp(tCase.expected, out) && "Test case failed");
    free(out);
}

//NOLINTBEGIN cppcoreguidelines-narrowing-conversions
const char BIG_INPUT[] = {
#embed "./tests/big.csv" if_empty('X', '\n')
    , '\0'
};

const char ISLAND_INPUT[] = {
#embed "./tests/island.csv" if_empty('X', '\n')
    , '\0'
};

const char ONE_COLUMN_INPUT[] = {
#embed "./tests/oneColumn.csv" if_empty('X', '\n')
    , '\0'
};

const char ONE_ROW_INPUT[] = {
#embed "./tests/oneRow.csv" if_empty('X', '\n')
    , '\0'
};

const char BIG_OUTPUT[] = {
#embed "./tests/big.txt" if_empty('X', '\n')
    , '\0'
};

const char ISLAND_OUTPUT[] = {
#embed "./tests/island.txt" if_empty('X', '\n')
    , '\0'
};

const char ONE_COLUMN_OUTPUT[] = {
#embed "./tests/oneColumn.txt" if_empty('X', '\n')
    , '\0'
};

const char ONE_ROW_OUTPUT[] = {
#embed "./tests/oneRow.txt" if_empty('X', '\n')
    , '\0'
};
//NOLINTEND

const TestCase TEST_CASES[] = {
	{ .input = (char*)BIG_INPUT, .expected = (char*)BIG_OUTPUT },
	{ .input = (char*)ISLAND_INPUT, .expected = (char*)ISLAND_OUTPUT },
	{ .input = (char*)ONE_ROW_INPUT, .expected = (char*)ONE_ROW_OUTPUT },
	{ .input = (char*)ONE_COLUMN_INPUT, .expected = (char*)ONE_COLUMN_OUTPUT },
};

int main(void)
{
	int totalTestCases = sizeof(TEST_CASES) / sizeof(TestCase);
	for (int i = 0; i < totalTestCases; i++) {
		assertTestCase(TEST_CASES[i]);
	}
}
