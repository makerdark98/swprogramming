#pragma once
#include "keyword.h"
#include <string.h>
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
			return target + (i - k);
		}
	}
	free(pi);
	return NULL;
}
/*
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
	int originalDataLength = dataLength;
	char* nowSearchPoint = data;
	while (nowSearchPoint != NULL) {
		nowSearchPoint = kmp(nowSearchPoint, dataLength, pattern, patternLength);
		if (nowSearchPoint != NULL) {
			nowSearchPoint += patternLength;
			dataLength = originalDataLength - (nowSearchPoint - data);
			if (result != NULL) {
				appendHeadNode(&result, NewNode(nowSearchPoint - patternLength));
			}
			else {
				result = NewNode(nowSearchPoint - patternLength);
			}
		}
	}
	return result;
}

int extractSentence(char** sentenceFirst, const char * originalStartPoint, const char * endPoint, char* keywordPoint)
{
	int sentenceLength = 0;
	char *frontDot, *behindDot;
	// find frontDot;
	for (frontDot = keywordPoint; *frontDot != '.' && frontDot > originalStartPoint; frontDot--);
	// find behindDot;
	for (behindDot = keywordPoint; *behindDot != '.' && behindDot < endPoint; behindDot++);
	sentenceLength = behindDot - frontDot;
	if (frontDot == originalStartPoint) *sentenceFirst = frontDot;
	else *sentenceFirst = (frontDot + 1);
	return sentenceLength;
}

int getNumSideChar(const char* originalStartPoint, const char* endPoint, char* keywordPoint, int lengthKeyword) {
	int f = 0, b = 0;
	for (f = 0; originalStartPoint <= keywordPoint - f-1; f++) {
		if (isWhitespace(*(keywordPoint - f-1))) break;
	}
	for (b = 0; endPoint >= keywordPoint + b; b++) {
		if (isWhitespace(keywordPoint[lengthKeyword+b])) break;
	}
	return f > b ? f : b;
}
int isMonolingual(const char * originalStartPoint, const char * endPoint, char * keywordPoint, int lengthKeyword)
{
	if (getNumSideChar(originalStartPoint, endPoint, keywordPoint, lengthKeyword) == 0) return 1;
	return 0;
}

int isWhitespace(char c)
{
	return c == ' ' || c == '\t' || c == '\n' || c == '\0';
}

void changeToLower(char * data)
{
	for (int i = 0; data[i] != '\0'; i++)
		data[i] = tolower(data[i]);
}
