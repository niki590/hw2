#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "User.h"
#include "defs.h"

typedef struct User_t {
	char* name;
	NODE* friends_list;
	int friend_count;
}USER;


//******************************************************************************
//* function name :User_Create
//* Description :recieves a name and creates a new user
//* Parameters:new user name
//* Return Value: pointer to new user struct
//******************************************************************************
PUSER User_Create(char* newname) 
{
	if (newname==NULL) //checks if input name is legit
		return NULL;
	PUSER s = (PUSER)malloc(sizeof(USER));
	if (s == NULL) 
		return NULL;
	s->friends_list = link_create();
		if (s->friends_list == NULL)
			return NULL;
		s->name = malloc(strlen(newname) + 1);
		if (s->name == NULL)
			return NULL;
		strcpy(s->name, newname);
		s->friend_count = 0;
	return s;      //user has been created successfully - return pointer to the new user
}
//******************************************************************************
//* function name :User_Delete
//* Description :Deletes existing user
//* Parameters:pointer to User 
//* Return Value: 
//******************************************************************************
void User_Delete(PUSER user)
{
	link_delete(user->friends_list);
	free(user->name);
	free(user);
}
//******************************************************************************
//* function name :User_addFriend
//* Description :add a friend to another users friend list if that friend isnt already there.
//*and increase the user's friend count
//* Parameters:pointer to User and name of friend to be added
//* Return Value: FAILURE/SUCCESS
//******************************************************************************
Result User_addFriend(PUSER name1, char* name2,Result a)
{
	Result already_connected = link_find(name1->friends_list, name2);
	if (already_connected) 
		return FAILURE;
	else
	{
		char *save = malloc(strlen(name2) + 1);
		if (save == NULL)
			a = SUCCESS;
		strcpy(save, name2);
		Result malloc_check =link_push(name1->friends_list, save);
		if (!malloc_check)
		{
			a = SUCCESS;			// indicates that malloc failed
			return FAILURE;
		}
		name1->friend_count++;	//increase the given user's friend count
	}
	return SUCCESS;
}

//******************************************************************************
//* function name :User_removeFriend
//* Description :remove a friend from another users friend list if that friend is there.
//*and decrease the user's friend count
//* Parameters:pointer to User and name of friend to be removed
//* Return Value: FAILURE/SUCCESS
//******************************************************************************
Result User_removeFriend(PUSER name1, char* name2) {
	Result does_exist = link_find(name1->friends_list, name2);
		if (!does_exist)
			return FAILURE;
		else
		{
			link_find_delete(name1->friends_list, name2);
			name1->friend_count--;	//decrease the given user's friend count
		}
		return SUCCESS;
}
//******************************************************************************
//* function name :User_getName
//* Description :return user's name using a given PUSER
//* Parameters:pointer to User
//* Return Value: User's "name" field
//******************************************************************************
char* User_getName(PUSER user_name){
	if (user_name == NULL)
	{
		printf("given pointer to getname is null");
		return NULL;
	}
	return user_name->name;
}
//******************************************************************************
//* function name :User_getFriendsList
//* Description :return pointer to the beginning of given user's friends list
//* Parameters:pointer to User
//* Return Value: pointer to User's friends list
//******************************************************************************
NODE* User_getFriendsList(PUSER user_name) {
	if (user_name == NULL) {
		printf(" Null ptr during attempt to get friends list");
		return NULL;
	}
	return user_name->friends_list;
}
//******************************************************************************
//* function name :User_getFriendsNum
//* Description :return number of friends of a certain user
//* Parameters:pointer to User
//* Return Value: friend count
//******************************************************************************
int User_getFriendsNum(PUSER user_name) 
{
	if (user_name == NULL) {
		printf("termination cause: Null ptr during attempt to get a friend count");
		return 0;
	}
	return user_name->friend_count;
}

//******************************************************************************
//* function name :User_print
//* Description :prints a user's friends list
//* Parameters:pointer to User
//* Return Value:
//******************************************************************************
void User_print(PUSER user_name) 
{
	if (user_name->friend_count == 0)
	{
		printf("User's name: %s\nThe user has 0 friends\n", user_name->name);
		return;
	}
	if (user_name->friend_count == 1) {
		printf("User's name: %s\nThe user has 1 friend:\n", user_name->name);
		link_print(user_name->friends_list);
		return;
	}
	else
	{
		printf("User's name: %s\nThe user has %d friends:\n", user_name->name, user_name->friend_count);
		link_print(user_name->friends_list);
	}
		return;
}
struct Node_t {
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
	NODE* new_node = (NODE*)malloc(sizeof(NODE));
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
Result link_find_delete(NODE* head, char* name)
{
	NODE* ptr_curr = head->next;
	NODE* ptr_prev = head;
	while (ptr_curr != NULL)
	{
		if (strcmp(ptr_curr->data, name) == 0)
		{
			ptr_prev->next = ptr_curr->next;
			free(ptr_curr->data);
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