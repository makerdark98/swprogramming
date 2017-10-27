#pragma once

#include "linkedlist.h"
int* getPrefix(char *pattern, int psize);
int kmp(char *target, int tsize, char *pattern, int psize);
Node* findKeyword(const char* data, const char* pattern);