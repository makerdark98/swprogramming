#pragma once
#include <stdio.h>
#include <string.h>
#include <io.h>
#include "linkedlist.h"
Node* newFileNode(char* filename);
Node* getFileList(char* path);
void destroyFileList(Node* head);