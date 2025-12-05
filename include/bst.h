#ifndef BST

#define BST

#include "ds_common.h"

typedef struct bstNode{
    void* value;
    void* key;
    struct bstNode *left, *right;
}BSTNode;

typedef struct Tree{
    BSTNode* head;
    cmp_func cmpFunc;
    int size;
}Tree;

Tree* bst_create(cmp_func cmp);
BSTNode* nodeT_create(void* key, void* value);
void bst_insert(void* key, Tree* tree, void* value);
BSTNode* bst_find(void* key, Tree* tree, BSTNode** parents);
int bst_remove(void* key, Tree* tree);
void bst_destroyn(BSTNode* node, free_func free);
void bst_destroy(Tree* tree, free_func free);
int BSTmode(void);


#endif