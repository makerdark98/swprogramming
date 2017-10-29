#if defined(_WIN32) || defined(WIN32)

#define OS_Windows 1
#include "main.h"
#define GetCurrentDir _getcwd
#define NumberOfThread 4
#endif
int LLLLL = 0;
char* Keyword;
int main(int argc, char* argv[]) {	//argv[1] : pattern string
	char path[100];
	for (int i = 0; i < 100; i++) {
		clock_t start = clock();
		GetCurrentDir(path, 100);
		Keyword = argv[1];
		int numProcessor = getNumberOfProcessor();
		if (numProcessor == 1) {

		}
		else {
			HANDLE hThread[NumberOfThread];
			DWORD ThreadID[NumberOfThread];
			ThreadData threadData[NumberOfThread];
			int numFile;
			Node *filelist = getFileList(path, &numFile);
			int* degFile = (int*)malloc(numFile * sizeof(int));
			for (int i = 0; i < NumberOfThread; i++) {
				threadData[i].Length = ceil(numFile / NumberOfThread);
				threadData[i].startPoint = filelist;
				int idx = numFile / NumberOfThread * i;
				for (int j = 0; j < idx; j++) {
					threadData[i].startPoint = threadData[i].startPoint->next;
				}
				threadData[i].degData = degFile + idx;
			}
			for (int i = 0; i < NumberOfThread; i++) {
				hThread[i] = CreateThread(NULL, 0, CheckData, &threadData[i], 0, &ThreadID[i]);
			}
			int numEndThread = 0;
			while (numEndThread != NumberOfThread) {
				numEndThread = 0;
				for (int i = 0; i < NumberOfThread; i++) {
					if (WaitForSingleObject(hThread[i], 0) == WAIT_OBJECT_0) {
						numEndThread++;
					}
				}
				Sleep(0);
			}
			for (int i = 0; i < NumberOfThread; i++) {
				CloseHandle(hThread[i]);
			}
			for (int i = 0; i < numFile; i++) {
				//printf("%d\n", degFile[i]);
			}
			free(degFile);
			destroyFileList(filelist);
		}
		double result = (double)(clock() - start) / CLOCKS_PER_SEC;
		printf("%2.5lf\n", result);
	}

	return 0;
}

int getNumberOfProcessor()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	return si.dwNumberOfProcessors;
}

DWORD WINAPI CheckData(LPVOID lpParameter)
{
	ThreadData P = *(ThreadData*)lpParameter;
	for (int i = 0; i < P.Length && P.startPoint!=NULL; i++) {
		//TODO : get Degree of Document;
		P.degData[i] = 0;
		HANDLE hFile = CreateFileA(P.startPoint->Data, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		//Error 2
		if (hFile == INVALID_HANDLE_VALUE)
			break;

		LARGE_INTEGER size;
		DWORD dwRead;
		GetFileSizeEx(hFile, &size);
		char* data = (char*)malloc(size.QuadPart);
		ReadFile(hFile, data, size.QuadPart, &dwRead, NULL);
		CloseHandle(hFile);
		Node* find_point = findKeyword(data, Keyword);
		Node* tmp2 = find_point;
		int length = 0;
		while (tmp2 != NULL) {
			length++;
			tmp2 = tmp2->next;
		}
		LLLLL++;
		P.degData[i] = length;
		destroyNode(find_point);
		free(data);
		P.startPoint = P.startPoint->next;
	}
	return 0;
}
