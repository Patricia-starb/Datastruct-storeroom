#include "bst.h"
#include "ds_common.h"
#include <stdlib.h>
#include <stdio.h>


Tree* bst_create(cmp_func cmp){
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->cmpFunc = cmp;
    tree->head = NULL;
    tree->size = 0;
    return tree;
}

BSTNode* node_create(void* key, void* value){
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->key = key;
    node->value = value;
    node->right = NULL;
    node->left = NULL;
    return node;
}

void bst_insert(void* key, Tree* tree, void* value){
    BSTNode* node = node_create(key, value);
    BSTNode* contrast = tree->head;
    cmp_func method = tree->cmpFunc;
    if(tree->size == 0){
        tree->head = node;
        tree->size += 1;
        return;
    }
    while(1){
        int result = method(contrast->key, key);
        if(result == 0){
            printf("There is already a equal key,please input another key.");
            return;
        }
        if(result > 0){
            if(contrast->left == NULL){
                contrast->left = node;
                tree->size++;
                break;
            }
            contrast = contrast->left;
            continue;
        }else{
            if(contrast->right == NULL){
                contrast->right = node;
                tree->size++;
                break;
            }
            contrast = contrast->right;
            continue;
        }
    }
    return;    
}//use ds_common

BSTNode* bst_find(void* key, Tree* tree, BSTNode** parents){
    BSTNode* node = tree->head;
    while(node != NULL){
        int result = tree->cmpFunc(node->key, key);
        if(result == 0){
            return node;
        }
        if(result > 0){
            *parents = node;
            node = node->left;
        }else{
            *parents = node;
            node = node->right;
        }
    }
    printf("No found.");
    return NULL;
}
//Binary inorder traversal
void bitTree(BSTNode* node, void** bitArray, int* index){
    
    if(node->left){
        bitTree(node->left, bitArray, index);
    }
    bitArray[(*index)++] = node->key;
    if(node->right){
        bitTree(node->right, bitArray, index);
    }
    return;
}

void bst_remove(void* key, Tree* tree){
    void** bitArray = (void**)malloc(sizeof(void*) * tree->size);
    int index = 0;
    BSTNode *node, *parents = NULL;
    BSTNode* targetn = bst_find(key, tree, &parents); 
    if(targetn == NULL) return;
    int choose = tree->cmpFunc(parents->key, key); 
    //childless
    if(targetn->left == NULL && targetn->right == NULL){
        if(choose > 0) parents->left = NULL;
        else parents->right = NULL;
        node_free(targetn);
    }else if(targetn->left == NULL){        //only child
        if(choose > 0) parents->left = targetn->right;
        else parents->right = targetn->right;
        node_free(targetn);
    }else if(targetn->right == NULL){
        if(choose > 0) parents->left = targetn->left;
        else parents->right = targetn->left;
        node_free(targetn);
    }else{    
        bitTree(tree->head, bitArray, &index);                               //gemini
        while(key != bitArray[index]){
            index++;
        }
        node = bst_find(bitArray[index-1], tree, &parents);
        targetn->key = node->key; targetn->value = node->value;
        bst_remove(node->key, tree);
    }
    tree->size--; 
    node_free(bitArray);
}//There are three cases: childless, only child and gemini.

void bst_destroyn(BSTNode* node, free_func free){
    if(node->left){
        bst_destroyn(node->left, free);
    }
    if(node->right){
        bst_destroyn(node->right, free);
    }
    free(node);
    return;
}//free()

void bst_destroy(Tree* tree, free_func free){
    bst_destroyn(tree->head, free);
    free(tree);
    return;
}
