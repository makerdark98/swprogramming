#if defined(_WIN32) || defined(WIN32)

#define OS_Windows 1
#include "main.h"
#define GetCurrentDir _getcwd
#endif

int main(int argc, char* argv[]) {	//argv[1] : pattern string
	for (int i = 0; i < 100; i++) {
		clock_t start_point = clock();
		if (argc == 1) {
			printf("Please Input argument\n");
			return 0;
		}
		char path[100];
		GetCurrentDir(path, 100);
		Node *filelist = getFileList(path);
		Node *tmp = filelist;
		while (filelist != NULL) {
			FILE *fin = fopen(filelist->Data, "r");
			fseek(fin, 0, SEEK_END);
			int fsize = ftell(fin);
			fseek(fin, 0, SEEK_SET);
			char* data = (char*)malloc(fsize);
			fread(data, fsize, 1, fin);
			Node* find_point = findKeyword(data, argv[1]);
			Node* tmp2 = find_point;
			int length = 0;
			while (tmp2 != NULL) {
				//printf("%d\n", tmp2->Data-data);
				length++;
				tmp2 = tmp2->next;
			}
			//printf("%d\n", length);
			destroyNode(find_point);
			free(data);
			fclose(fin);
			filelist = filelist->next;
		}
		destroyFileList(filelist);
		double result = (double)(clock() - start_point) / CLOCKS_PER_SEC;
		printf("%5.2f\n", result);
	}
	return 0;
}
