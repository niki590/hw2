#ifndef List_h
#define List_h
#define MAX_LEN 256
#include "defs.h"

typedef struct Node_t NODE;

NODE*  link_create();
Result link_push(NODE* head, char* data);
void   link_delete(NODE* head);
Result link_find_delete(NODE* head, char* name);
Result link_print(NODE* head);
Result link_find(NODE* head, char* name);

#endif //List_h