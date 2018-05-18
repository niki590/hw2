#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "User.h"
#include "SocialNetwork.h"



typedef struct Node_u {
	PUSER data;
	struct Node_u *next;
}UNODE;

//create the start of network by pointer to node
static PUNODE network = NULL ;


//******************************************************************************
//* function name : ulink_create
//* Description : creates a node in linked list and returns pointer to it
//* Parameters: NA
//* Return Value: pointer to the node
//******************************************************************************
PUNODE ulink_create()
{
	UNODE* new_node = (UNODE*)malloc(sizeof(UNODE));
	if (new_node == NULL)
	{
		printf("malloc for node failed");
		Network_delete();
	}
	new_node->data = NULL;
	new_node->next = NULL;
	return new_node;
}
//******************************************************************************
//* function name : ulink_push
//* Description :  inserts new node with given data in front of the list
//* Parameters: in- pointer to UNODE 
//* Return Value: success or failure 
//******************************************************************************
Result ulink_push(PUNODE in)
{
	if (in == NULL) {
		printf("null pointer to ulink push");
		return FAILURE;
	}
	in->next = network;
	network = in;
	return SUCCESS;
}

//******************************************************************************
//* function name : Network_delete()
//* Description : delete the whole list of network
//* Parameters: NA
//* Return Value: SUCCESS OR FAILURE
//******************************************************************************
Result Network_delete()
{
	PUNODE ptr = network;
	PUNODE ptr_next = NULL;
	while (ptr != NULL)
	{
		ptr_next = ptr->next;
		User_Delete(ptr->data);
		free(ptr);
		ptr = ptr_next;
	}
	network = NULL;
	return SUCCESS;
}

//******************************************************************************
//* function name : ulink_find
//* Description : checks if there is a node which the user it points on	
//                is the same as name given
//* Parameters: head- pointer to the head of linked list
//				name- the name of the guy which i wana find
//* Return Value: FAILURE or SUCCESS 
//******************************************************************************
PUSER ulink_find(char* name)
{
	if (name == NULL)
	{
		printf("null pointer to ulink_find");
	}
	PUNODE ptr_curr = network;
	while (ptr_curr != NULL)
	{
		if (strcmp(User_getName(ptr_curr->data), name) == 0)
			return ptr_curr->data;
		ptr_curr = ptr_curr->next;
	}
	return NULL;
}

//******************************************************************************
//* function name :  Network_addUser
//* Description : gets 2 names of inviter and invited, and if 
//				  all the given conditions are correct makes user
//* Parameters:  inviter - name of inviter, invited- name of invited 
//* Return Value: success or failure of function
//******************************************************************************
Result Network_addUser(char* invited, char* inviter)
{
	if ((inviter == NULL) && (network==NULL))   //check if it is the first person 
	{
		PUNODE new_one = ulink_create();
		if (new_one == NULL)
		{
			printf("malloc in network_adduser failed,exiting");
			Network_delete();
			exit(1);
		}
			
		new_one->data= User_Create(invited);
		if (new_one->data == NULL)
		{
			Network_delete();
			printf("malloc for new user failed");
			exit(1);
		}	
		network = new_one;
		new_one->next = NULL;
		return SUCCESS;
	}
	PUSER invited_exist = ulink_find( invited);
	PUSER inviter_exist= ulink_find( inviter);
	if ((inviter_exist==NULL) || (invited_exist!=NULL)) 
		return FAILURE; 
	PUNODE new_one = ulink_create();   // everything is fine with both, make the connection
	if (new_one == NULL)
	{
		Network_delete();
		printf("malloc for new user failed");
		exit(1);
	}
	new_one->data = User_Create(invited);
	if (new_one->data == NULL)
	{
		Network_delete();
		printf("malloc for new user failed");
		exit(1);
	}
	Result check = ulink_push(new_one);
	check = Network_addRelationship(inviter, invited);
	if (!check)
		return FAILURE;
	return SUCCESS;
}

//******************************************************************************
//* function name :Network_addRelationship
//* Description :add a friend to another users friend list and vice versa 
//* if that relationship doesnt already exist.
//* Parameters:names of users to be connected
//* Return Value: FAILURE/SUCCESS
//******************************************************************************
Result Network_addRelationship(char* name1, char* name2)
{
	//check for existing users with given names
	PUSER user1 = ulink_find(name1);
	if (user1 == NULL)return FAILURE;
	PUSER user2 = ulink_find(name2);
	if (user2 == NULL)return FAILURE;
	//check if relationship exists, if it doesnt than makes relationship between the two users
	Result a = FAILURE;
	Result b = FAILURE;
	Result check_relationship1 = User_addFriend(user1, name2,a);
	Result check_relationship2 = User_addFriend(user2, name1,b);
	if (a || b) 
	{
		printf("malloc in addrelationship failed");
		Network_delete();
		exit(1);
	}
	return (check_relationship1 && check_relationship2);
}

//******************************************************************************
//* function name :Network_removeRelationship
//* Description :remove a friend from another users friend list and vice versa 
//* in case relationship already exists.
//* Parameters:names of users to be disconnected
//* Return Value: FAILURE/SUCCESS
//******************************************************************************
Result Network_removeRelationship(char* name1, char* name2)
{
	//check if vaild names
	if ((strlen(name1) > MAX_LEN) || (strlen(name2) > MAX_LEN))
	{
		printf("names logner then 256");
		return FAILURE;
	}
	//check for existing users with given names
	PUSER user1 = ulink_find(name1);
	if (user1 == NULL)return FAILURE;
	PUSER user2 = ulink_find(name2);
	if (user2 == NULL)return FAILURE;
	//check if friend count of these users is bigger than 1
	//if it isnt returns FAILURE
	int frcount1 = User_getFriendsNum(user1);
	if (frcount1 <= 1)return FAILURE;
	int frcount2 = User_getFriendsNum(user2);
	if (frcount2 <= 1)return FAILURE;
	//check if relationship exists, if it doesnt than makes relationship between the two users
	Result check_relationship1 = User_removeFriend(user1, name2);
	Result check_relationship2 = User_removeFriend(user2, name1);
	return check_relationship1 && check_relationship2;
}

//******************************************************************************
//* function name :Network_print
//* Description :print all users in network and for each one print their friends list 
//* Parameters:
//* Return Value: SUCCESS OR FAILURE
//******************************************************************************
Result Network_print()
{
	PUNODE curr_user = network;
	printf("The social network contains the users:\n");
	while (curr_user != NULL) {
		User_print(curr_user->data);
		printf("\n");
		curr_user = curr_user->next;
	}
	return SUCCESS;
}
