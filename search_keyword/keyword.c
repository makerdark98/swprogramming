#pragma once
#include "keyword.h"
/*	만약 strstr 을 못쓰게 하셨을 경우를 대비한 kmp 알고리즘으로 짠 데이터
int * getPrefix(char * pattern, int psize)
{
	int k = -1;
	int i = 1;
	int *pi = malloc(sizeof(int)*psize);
	if (!pi) return NULL;
	pi[0] = k;
	for (i = 1; i < psize; i++) {
		while (k > -1 && pattern[k + 1] != pattern[i])
			k = pi[k];
		if (pattern[i] == pattern[k + 1])
			k++;
		pi[i] = k;
	}
	return pi;
}

int kmp(char * target, int tsize, char * pattern, int psize)
{
	int i;
	int *pi = getPrefix(pattern, psize);
	int k = -1;
	if (!pi) return -1;
	for (i = 0; i < tsize; i++) {
		while (k > -1 && pattern[k + 1] != target[i])
			k = pi[k];
		if (target[i] == pattern[k + 1])
			k++;
		if (k == psize - 1) {
			free(pi);
			return i - k;
		}
	}
	free(pi);
	return -1;
}

Node* findKeyword(const char * data, const char * pattern)
{
	Node* result = NULL;
	int nowPoint = 0, dataLength = strlen(data), patternLength = strlen(pattern);
	while (nowPoint < dataLength) 
	{
		nowPoint += kmp(data+nowPoint, dataLength-nowPoint, pattern, patternLength);
		nowPoint += patternLength;
		if (nowPoint == -1) break;
		if (result == NULL) result = NewNode(data + nowPoint);
		else AppendNode(result, NewNode(data + nowPoint));
	}
	return result;
}
*/
Node* findKeyword(const char * data, const char * pattern)
{
	Node* result = NULL;
	int dataLength = strlen(data), patternLength = strlen(pattern);
	char* nowSearchPoint = data;
	while (nowSearchPoint !=NULL) {
		nowSearchPoint = strstr(nowSearchPoint, pattern);
		if (nowSearchPoint !=NULL) {
		nowSearchPoint += patternLength;
			if (result != NULL) {
				appendHeadNode(&result, NewNode(nowSearchPoint-patternLength));
			}
			else {
				result = NewNode(nowSearchPoint-patternLength);
			}
		}
	}
	return result;
}