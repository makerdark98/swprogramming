#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <direct.h>
#include "linkedlist.h"
#include "keyword.h"
#include "file.h"
#include <Windows.h>


int main(int argc, char* argv[]);
int getNumberOfProcessor();
typedef struct __threadData {
	Node* startPoint;
	int Length;
	int* degData;
}ThreadData;
DWORD WINAPI CheckData(LPVOID lpParameter);