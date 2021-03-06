#pragma once

#include "linkedlist.h"
//int* getPrefix(char *pattern, int psize);
//int kmp(char *target, int tsize, char *pattern, int psize);
Node* findKeyword(const char* data, const char* pattern);
int extractSentence(char** sentenceFirst, const char * originalStartPoint, const char * endPoint, char* keywordPoint);
int getNumSideChar(const char* originalStartPoint, const char* endPoint, char* keywordPoint, int lengthKeyword);
int isMonolingual(const char* originalStartPoint, const char* endPoint, char* keywordPoint, int lengthKeyword);
int isWhitespace(char c);
void changeToLower(char* data);