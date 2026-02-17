#include "strbuild.h"
#include "strutil.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void padding(void)
{
	char* alreadyEnough = padLeft("123", 3, '0');
	assert(!strcmp(alreadyEnough, "123") && "Characters are not added to an already long enough string");
	free(alreadyEnough);

	alreadyEnough = padLeft("123", 2, '0');
	assert(!strcmp(alreadyEnough, "123") && "Characters are not added to an already long enough string");
	free(alreadyEnough);

	alreadyEnough = padRight("123", 3, '0');
	assert(!strcmp(alreadyEnough, "123") && "Characters are not added to an already long enough string");
	free(alreadyEnough);

	alreadyEnough = padRight("123", 2, '0');
	assert(!strcmp(alreadyEnough, "123") && "Characters are not added to an already long enough string");
	free(alreadyEnough);

	char* correctPadding = padLeft("1234", 6, '0');
	assert(!strcmp(correctPadding, "001234") && "Strings are correctly padded");
	free(correctPadding);
	
	correctPadding = padRight("1234", 6, '0');
	assert(!strcmp(correctPadding, "123400") && "Strings are correctly padded");
	free(correctPadding);
}

void builder(void)
{
	StringBuilder* builder = stringBuilderNew();
	assert(builder != NULL && "A new string builder has been initialized");

	char* s1 = stringBuild(builder);
	assert(!strcmp(s1, "") && "String builder emits an empty string by default");
	free(s1);

	char* someLongString = "ABCABCEHFIUOWHGPLVKJBRUHIVKNBERSUGIHLCKENJ";
	stringBuilderAppend(builder, someLongString);
	char* s2 = stringBuild(builder);
	assert(!strcmp(s2, someLongString) && "String has been properly attached");
	free(s2);

	char* someLongStringPlus = "ABCABCEHFIUOWHGPLVKJBRUHIVKNBERSUGIHLCKENJ123";
	stringBuilderAppend(builder, "123");
	char* s3 = stringBuild(builder);
	assert(!strcmp(s3, someLongStringPlus) && "String has been properly attached");
	free(s3);

	stringBuilderFree(&builder);
	assert(builder == NULL && "The string builder has been freed");
}

int main(void)
{
	builder();
	padding();
	return 0;
}
