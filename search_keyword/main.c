#if defined(_WIN32) || defined(WIN32)

#define OS_Windows 1
#include "main.h"
#define GetCurrentDir _getcwd
#define NumberOfThread 4
//#define TIME_CHECK
#endif
char* Keyword;
char path[100];
int main(int argc, char* argv[]) {
	if (argc == 1) {
		printf("Please Input argument\n");
		return 0;
	}
	changeToLower(argv[1]);
	GetCurrentDir(path, 100);
	Keyword = argv[1];
	HANDLE hThread[NumberOfThread];
	DWORD ThreadID[NumberOfThread];
	ThreadData threadData[NumberOfThread];
	int numFile;
	Node *filelist = getFileList(path, &numFile);
	FNodeRank* degFile = (FNodeRank*)malloc(numFile * sizeof(FNodeRank));
	for (int i = 0; i < NumberOfThread; i++) {
		int idx = ceil((double)numFile / NumberOfThread) * i;
		threadData[i].Length = ceil((double)numFile / NumberOfThread);
		threadData[i].startPoint = filelist;
		for (int j = 0; j < idx; j++) {
			if (threadData[i].startPoint != NULL) threadData[i].startPoint = threadData[i].startPoint->next;
		}
		threadData[i].rank = degFile + idx;
	}
	for (int i = 0; i < NumberOfThread; i++) {
		hThread[i] = CreateThread(NULL, 0, CheckData, &threadData[i], 0, &ThreadID[i]);
	}
	int numEndThread = 0;
	WaitForMultipleObjects(4, hThread, TRUE, INFINITE);

	for (int i = 0; i < NumberOfThread; i++) {
		CloseHandle(hThread[i]);
	}
	qsort(degFile, numFile, sizeof(FNodeRank), compare);
	for (int i = 0; i < numFile; i++) {
		if (degFile[i].Rank > 1) printf("%s\n", degFile[i].DataNode->Data);
	}
	free(degFile);
	destroyFileList(filelist);
	return 0;
}

DWORD WINAPI CheckData(LPVOID lp)
{
	ThreadData P = *(ThreadData*)lp;
	for (int i = 0; i < P.Length && P.startPoint != NULL; i++) {
		char fullPath[200];
		LARGE_INTEGER size;
		DWORD dwRead;
		P.rank[i].Rank = 0;
		sprintf(fullPath, "%s\\%s", path, P.startPoint->Data);
		HANDLE hFile = CreateFileA(fullPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
			break;
		GetFileSizeEx(hFile, &size);
		char* data = (char*)malloc(size.QuadPart + 1);
		data[size.QuadPart] = '\0';
		ReadFile(hFile, data, size.QuadPart, &dwRead, NULL);
		CloseHandle(hFile);
		changeToLower(data);
		Node* find_point = findKeyword(data, Keyword);
		Node* tmp2 = find_point;
		int rank = 0;
		while (tmp2 != NULL) {
			rank += (4 - getNumSideChar(data, data + size.QuadPart, tmp2->Data, strlen(Keyword))) * 10;
			tmp2 = tmp2->next;
		}
		P.rank[i].Rank = rank;
		P.rank[i].DataNode = P.startPoint;
		destroyNode(find_point);
		free(data);
		P.startPoint = P.startPoint->next;
	}
	return 0;
}

int compare(void* first, void* second) {
	if (((FNodeRank*)first)->Rank == ((FNodeRank*)second)->Rank) {
		return strcmp(((FNodeRank*)first)->DataNode->Data, ((FNodeRank*)second)->DataNode->Data);
	}
	return ((FNodeRank*)first)->Rank > ((FNodeRank*)second)->Rank ? -1 : 1;
}