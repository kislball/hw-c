#include "list.h"
#include "map.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
	if (argc != 2) return 1;
	srand(time(nullptr)); //NOLINT(cert-msc51-cpp)
	char* fileName = argv[1];
	Map* db = mapOpen(fileName);
	LinkedList* keys = mapGetKeys(db);
	int totalKeys = linkedListCount(keys);

	for (int i = 0; i < 50000; i++) {
		int keyIdx = rand() % totalKeys; //NOLINT(cert-msc50-cpp)
		char* key;
		linkedListGet(keys, keyIdx, (void**)&key);
		char* value;
		mapGet(db, key, &value);
	}

	return 0;
}
