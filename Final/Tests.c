/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "List.h"
#include "User.h"
#include "SocialNetwork.h"

void Link_check()
{
	NODE* niki = link_create();
	link_push(niki, "1");
	link_push(niki, "niki");
	link_push(niki, "ofry");
	link_print(niki);
	bool a=link_find(niki, "3");
	link_find_delete(niki, "niki");
	link_print(niki);
	link_delete(niki); 
}


/*void User_check()
{
	PUSER niki = User_Create("ofry ha gever");
	bool check = User_addFriend(niki, "ofry");
	check = User_addFriend(niki, "shimi");
	check = User_addFriend(niki, "shuli");
	check = User_addFriend(niki, "alon");
	if (User_getFriendsNum(niki)!= 4)
		printf("friend count is wrong\n");
	 check = User_removeFriend(niki, "shimi");
	 check = User_removeFriend(niki, "shimi");
	 if (( check) || (User_getFriendsNum(niki) != 3))
		 printf("remove doesnt work well\n");
	if (User_getFriendsNum(niki)!=3)
		printf("remove or get freindnum doesnt work well\n");
	if (strcmp(User_getName(niki), "ofry ha gever")!= 0)
		printf("get name doesnt work well\n");
	NODE* friend1 = User_getFriendsList(niki);
	User_print(niki); 
}

void Social_check()
{
	Result a= Network_addUser("ofry", NULL);
	a = Network_addUser("niki", "ofry");
	a = Network_addUser("alon", "niki");
	a = Network_addUser("shuli", "ofry");
	Network_print();
	a = Network_addUser("ophiron", "ofry");
	a = Network_addUser("alon", "niki");
	a = Network_addRelationship("ophiron", "niki");
	Network_print();
	a = Network_addRelationship("ron", "niki");
	Network_print();
	a = Network_addUser("ron", "niki");
	Network_print();
	Network_addRelationship("ron", "ofry");
	Network_print();
	Network_delete();
}
int main()
{
	Link_check();
	//User_check();
	Social_check();
	printf("lol");
	return 1;
}
*/