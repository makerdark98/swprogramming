#pragma once
#include "linkedlist.h"

Node * NewNode(char * Data)
{
	Node *tmp = (Node*)malloc(sizeof(Node));
	tmp->Data = Data;
	tmp->next = NULL;
	tmp->prev = NULL;
}

void appendNode(Node * head, Node * end)
{
	while (head->next != NULL) 
	{
		head = head->next;
	}
	head->next = end;
	if (end != NULL) end->prev = head;
}

void removeNode(Node * head, Node * node)
{
	while (head->next == node) 
	{
		head = head->next;
	}
	head->next = node->next;
	node->next->prev = head;
	deleteNode(node);
}

void deleteNode(Node * node)
{
	free(node);
}

void destroyNode(Node * head)
{
	Node* tmp;
	while (head != NULL) 
	{
		tmp = head;
		head = head->next;
		deleteNode(tmp);
	}
}

int getLengthList(Node * head)
{
	int length = 0;
	while (head != NULL) {
		head = head->next;
		length++;
	}
	return length;
}

void appendHeadNode(Node ** head, Node * end)
{
	end->next = (*head);
	(*head)->prev = end;
	(*head) = end;
}
