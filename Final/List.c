#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

struct Node_t{
	char* data;
	 struct Node_t *next;
};
//******************************************************************************
//* function name : link_print
//* Description : prints the linked list 
//* Parameters:  head- pointer to the head of linked list
//* Return Value: NA
//******************************************************************************
Result link_print(NODE* head)
{
	NODE* ptr = head->next;
	while (ptr != NULL)
	{
		printf("%s\n", ptr->data);
		ptr = ptr->next;
	}
	return SUCCESS;
}
//******************************************************************************
//* function name : link_create
//* Description : creates first node in linked list and returns pointer to it
//* Parameters: NA
//* Return Value: pointer to the node which is the linked list
//******************************************************************************
NODE* link_create()
{
	NODE* new_node = (NODE*)malloc(sizeof(NODE));
	if (new_node == NULL) 
		printf("malloc for node failed");
	new_node->data = NULL;
	new_node->next = NULL;
	return new_node;
}
//******************************************************************************
//* function name : link_push
//* Description : Given a pointer to pointer to the head of linked list
//inserts new node with given data in  front of the list
//* Parameters: head- pointer to pointer to the head of linked list 
//data - the info of new data needed to be added
//* Return Value: NA
//******************************************************************************
Result link_push(NODE* head, char* data)
{
	NODE* new_node = (NODE*) malloc(sizeof(NODE));
	if (new_node == NULL) {
		printf("malloc for node failed");
		return FAILURE;
	}
	new_node->data = data;
	new_node->next = head->next;
	head->next = new_node;
	return SUCCESS;
}

//******************************************************************************
//* function name : link_delete
//* Description : Given a pointer to the pointer of the linked list, delete the list
//* Parameters: head- pointer to pointer to the head of linked list 
//* Return Value: NA
//******************************************************************************
void link_delete(NODE* head)
{
	NODE* ptr = head;
	NODE* ptr_next = NULL;
	while (ptr != NULL)
	{
		ptr_next = ptr->next;
		free(ptr->data);
		free(ptr);
		ptr = ptr_next;
	}
	head = NULL;
}

//******************************************************************************
//* function name : link_find_delete
//* Description : finds the node which it's data is the same as data given 
//and deletes it
//* Parameters: head- pointer to pointer to the head of linked list
//				name- the name of the friend which i wana delete
//* Return Value: FAILURE or SUCCESS 
//******************************************************************************
Result link_find_delete(NODE* head,char* name)
{
	NODE* ptr_curr = head->next;
	NODE* ptr_prev = head;
	while (ptr_curr!= NULL)
	{
		if (strcmp(ptr_curr->data,name) == 0)
		{
			ptr_prev->next = ptr_curr->next;
			free(ptr_curr);
			return SUCCESS;
		}
		ptr_prev = ptr_curr;
		ptr_curr = ptr_curr->next;
	}
	return FAILURE;
}
//******************************************************************************
//* function name : link_find
//* Description : checks if there is a node which it's data is the same as data given 
//* Parameters: head- pointer to pointer to the head of linked list
//				name- the name of the friend which i wana find
//* Return Value: FAILURE or SUCCESS 
//******************************************************************************
Result link_find(NODE* head, char* name)
{
	NODE* ptr_curr = head->next;
	while (ptr_curr != NULL)
	{
		if (strcmp(ptr_curr->data, name) == 0)
			return SUCCESS;
		ptr_curr = ptr_curr->next;
	}
	return FAILURE;
}
