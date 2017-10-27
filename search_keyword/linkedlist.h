#pragma once
#include <stdlib.h>
typedef struct __Node {
	char* Data;
	struct __Node *next, *prev;
}Node;

Node* NewNode(char* Data);
void AppendNode(Node *head, Node *end);
void RemoveNode(Node *head, Node *node);
void DeleteNode(Node *node);
void DestroyNode(Node *head);