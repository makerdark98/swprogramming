#pragma once
#include <stdlib.h>
typedef struct __Node {
	char* Data;
	struct __Node *next, *prev;
}Node;

Node* NewNode(char* Data);
void appendNode(Node *head, Node *end);
void removeNode(Node *head, Node *node);
void deleteNode(Node *node);
void destroyNode(Node *head);
int getLengthList(Node *head);
void appendHeadNode(Node **head, Node *end);