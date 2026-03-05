#include "list.h"
#include "map.h"
#include <stdlib.h>
#include <time.h>

char* randomCode() {
	char* res = calloc(5, sizeof(char));

	res[0] = 'A' + (rand() % 25); //NOLINT
	res[1] = 'A' + (rand() % 25); //NOLINT
	res[2] = 'A' + (rand() % 25); //NOLINT
	res[3] = 'A' + (rand() % 25); //NOLINT

	return res;
}

int main(int argc, char** argv) {
	if (argc != 2) return 1;
	srand(time(nullptr)); //NOLINT(cert-msc51-cpp)
	char* fileName = argv[1];
	Map* db = mapOpen(fileName);
	LinkedList* keys = mapGetKeys(db);
	int totalKeys = linkedListCount(keys);

	for (int i = 0; i < 20000; i++) {
		if (i % 2 == 0) {
			int keyIdx = rand() % totalKeys; //NOLINT(cert-msc50-cpp)
			char* key = nullptr;
			linkedListGet(keys, keyIdx, (void**)&key);
			char* value;
			mapGet(db, key, &value);
		} else {
			char* code = randomCode();
			char* code2 = randomCode();
			linkedListInsert(keys, 0, code, false);
			mapInsert(&db, code, code2);
			free(code2); // code doesnt need to be freed, linked list takes care of that
			totalKeys++;
		}
	}

	return 0;
}
