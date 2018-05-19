#ifndef SocialNetwork_h
#define SocialNetwork_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "User.h"
#define MAX_LEN 256
//hi
typedef struct Node_u *PUNODE;

PUNODE ulink_create();
Result ulink_push(PUNODE in);
PUSER ulink_find(char* name);
Result Network_addUser(char* invited, char* inviter);
Result Network_addRelationship(char* invited, char* inviter);
Result Network_removeRelationship(char* invited, char* inviter);
Result Network_print();
Result Network_delete();

#endif//SocialNetwork_h