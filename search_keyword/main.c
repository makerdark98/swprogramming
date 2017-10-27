#if defined(_WIN32) || defined(WIN32)

#define OS_Windows 1
#include "main.h"

#endif


int main(int argc, char* argv[]) {
	for (int i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}
	FILE *fin = fopen("input.txt", "r");
	fseek(fin, 0, SEEK_END);
	long fsize = ftell(fin);
	fseek(fin, 0, SEEK_SET);
	char* data = (char*)malloc(fsize);
	fread(data, fsize, 1, fin);
	printf("%s", data);
	free(data);
	fclose(fin);
	return 0;
}
