#include "file.h"

Node* newFileNode(char* filename) {
	int length = strlen(filename);
	char* data = (char*)malloc(sizeof(char)*length+1);
	strcpy(data, filename);
	return NewNode(data);
}
Node* getFileList(char* path, int* count) {
	Node* result = NULL;
	char search_path[100];
	struct _finddata_t file_search;
	int h_file;
	sprintf(search_path, "%s/*.txt", path);
	h_file = _findfirst(search_path, &file_search);
	*count = 0;
	if (h_file != -1) {
		++(*count);
		result = newFileNode(file_search.name);
		while (_findnext(h_file, &file_search) == 0) {
			appendHeadNode(&result, newFileNode(file_search.name));
			++(*count);
		}
		_findclose(h_file);
	}
	return result;
}
void destroyFileList(Node* head) {
	Node* tmp;
	while (head != NULL) {
		tmp = head;
		head = head->next;
		free(tmp->Data);
		deleteNode(tmp);
	}
}
