#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "ds_common.h"

int main(void){
    Tree* tree = bst_create(int_cmp);
    int key[] = {1,2,3,4,5,6,7,8},index = 0;
    char value[] = {'a','b','c','d','e','f','g','h'};
    while(index < 8){
        bst_insert(&key[index], tree, &value[index]);
        index++;
    }

    BSTNode *node, *parents = NULL;
    int six = 6;
    node = bst_find(&six, tree, &parents);
    printf("key:%d\nvalue:%c\n", *(int*)(node->key), *(char*)(node->value));
    printf("Tree size:%d\n", tree->size);

    void** bitArray = (void**)malloc(sizeof(void*) * tree->size);
    index = 0;
    bitTree(tree->head, bitArray, &index);
    printf("Binary inorder traversal:\n");
    index = 0;
    while(index < tree->size){
        printf(" %d ", *(int*)(bitArray[index]));
        index++;
    }

    bst_remove(&six, tree);
    printf("\nTree size:%d\n", tree->size);
    node_free(bitArray);
    void** bitArrayNow = (void**)malloc(sizeof(void*) * tree->size);
    index = 0;
    bitTree(tree->head, bitArrayNow, &index);
    printf("Binary inorder traversal now:\n");
    index = 0;
    while(index < tree->size){
        printf(" %d ", *(int*)(bitArrayNow[index]));
        index++;
    }
    printf("\n");
    node_free(bitArrayNow);


    bst_destroy(tree, node_free);
}