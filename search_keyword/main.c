#if defined(_WIN32) || defined(WIN32)

#define OS_Windows 1
#include "main.h"
#include <time.h>
#endif
void testJustSearch(int argc, char* argv[]) {
	FILE *fin = fopen("input.txt", "r");
	fseek(fin, 0, SEEK_END);
	int fsize = ftell(fin);
	fseek(fin, 0, SEEK_SET);
	char* data = (char*)malloc(fsize);
	fread(data, fsize, 1, fin);
	Node* find_point = findKeyword(data, argv[1]);
	Node* tmp = find_point;
	/*while (tmp != NULL) {
		for (int i = 0; i < 3; i++) {
			printf("%c", tmp->Data[i]);
		}
		printf("\n");
		tmp = tmp->next;
	}
	*/
	destroyNode(find_point);
	free(data);
	fclose(fin);

}

int main(int argc, char* argv[]) {	//argv[1] : pattern string
	for (int i = 0; i < 100; i++) {
		clock_t before = clock();
		if (argc == 1) printf("No paramater\n");
		else testJustSearch(argc, argv);
		double result = (double)(clock() - before) / CLOCKS_PER_SEC;
		printf("%5.10f\n", result);
	}
	return 0;
}
