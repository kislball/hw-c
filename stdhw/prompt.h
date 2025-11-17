// clang-tidy по какой-то причине жалуется на двойное объявление, но при этом
// указывает на одно и то же место
// см https://github.com/kislball/hw-c/actions/runs/19425092224/job/55570610971?pr=12/
// NOLINTBEGIN
int prompt(char* data);
int* promptIntArray(char* prompt, int* len);
char* promptString(char* prompt);
// NOLINTEND
