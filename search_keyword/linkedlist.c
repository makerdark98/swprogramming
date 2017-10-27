#pragma once
#include "linkedlist.h"

Node * NewNode(char * Data)
{
	Node *tmp = (Node*)malloc(sizeof(Node));
	tmp->Data = Data;
	tmp->next = NULL;
	tmp->prev = NULL;
}

void AppendNode(Node * head, Node * end)
{
	while (head->next != NULL) 
	{
		head = head->next;
	}
	head->next = end;
	if (end != NULL) end->prev = head;
}

void RemoveNode(Node * head, Node * node)
{
	while (head->next == node) 
	{
		head = head->next;
	}
	head->next = node->next;
	node->next->prev = head;
	DeleteNode(node);
}

void DeleteNode(Node * node)
{
	free(node);
}

void DestroyNode(Node * head)
{
	Node* tmp;
	while (head->next != NULL) 
	{
		tmp = head;
		head = head->next;
		DeleteNode(tmp);
	}
}
