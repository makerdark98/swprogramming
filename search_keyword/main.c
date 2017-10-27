#if defined(_WIN32) || defined(WIN32)

#define OS_Windows 1
#include "main.h"

#include <crtdbg.h>
#endif
void func(int argc, char* argv[]) {
	for (int i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}
	FILE *fin = fopen("input.txt", "r");
	fseek(fin, 0, SEEK_END);
	int fsize = ftell(fin);
	fseek(fin, 0, SEEK_SET);
	char* data = (char*)malloc(fsize);
	fread(data, fsize, 1, fin);
	Node* find_point = findKeyword(data, argv[1]);
	Node* tmp = find_point;
	while (tmp != NULL) {
		for (int i = 0; i < 3; i++) {
			printf("%c", tmp->Data[i]);
		}
		printf("\n");
		tmp = tmp->next;
	}

	DestroyNode(find_point);
	free(data);
	fclose(fin);

}

int main(int argc, char* argv[]) {	//argv[1] : pattern string
	func(argc, argv);
	_CrtDumpMemoryLeaks();
	return 0;
}
