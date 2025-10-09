#ifndef LIST_STRUCT

#define LIST_STRUCT
#include "ds_common.h"

typedef struct Node{
    void* data;
    struct Node *front, *back;
}Node;

typedef struct List{
    Node* head;
    int size;
}List;

List* list_create();
Node* node_create();
void flist_insert(List* list, void* val);
void blist_insert(List* list, void* val);
Node* list_find(List* lsit, void* val, cmp_func cmp);
void list_remove(List* list, void* val, cmp_func cmp, free_func);
void list_destroy(List* list, free_func);


#endif