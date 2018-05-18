#ifndef User_h
#define User_h
#include "defs.h"
#define MAX_LEN 256
typedef struct Node_t NODE;

NODE*  link_create();
Result link_push(NODE* head, char* data);
void   link_delete(NODE* head);
Result link_find_delete(NODE* head, char* name);
Result link_print(NODE* head);
Result link_find(NODE* head, char* name);
typedef struct User_t* PUSER;
PUSER User_Create(char* name);
void User_Delete(PUSER name);
Result User_addFriend(PUSER name1, char* name2,Result a);
Result User_removeFriend(PUSER name1, char* name2);
char* User_getName(PUSER user_name);
NODE* User_getFriendsList(PUSER user_name);
int User_getFriendsNum(PUSER user_name);
void User_print(PUSER user_name);

#endif//User_h

