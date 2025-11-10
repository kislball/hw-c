#include "list.h"
#include "sortedList.h"
#include <assert.h>
#include <stdio.h>
#include <stdhw.h>
#include <stdlib.h>
#include <time.h>

#define TEST_STEPS 1000

int main(int argc, char** argv)
{
	srand(time(NULL));
	LinkedList list = linkedListNew();

	for (int i = 0; i < TEST_STEPS; i++) {
		if (rand() % 10 == 0) {
			int len = linkedListCount(&list);
			int target_idx = rand() % len;
			linkedListRemove(&list, target_idx);
		} else {
			int val = rand();
			sortedLinkedListInsert(&list, val);
		}		
	}

	int previous = list.head->value;
	LINKED_LIST_FOREACH(&list, node)
	{
		assert(previous <= node->value);
		previous = node->value;
	}

	linkedListDelete(&list);
	return 0;
}
