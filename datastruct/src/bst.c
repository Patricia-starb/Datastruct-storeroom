#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "ds_common.h"
#include "visual.h"
#include <ncurses.h>
#include <time.h>



Tree* bst_create(cmp_func cmp){
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->cmpFunc = cmp;
    tree->head = NULL;
    tree->size = 0;
    return tree;
}

BSTNode* nodeT_create(void* key, void* value){
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->key = key;
    node->value = value;
    node->right = NULL;
    node->left = NULL;
    return node;
}

void bst_insert(void* key, Tree* tree, void* value){
    BSTNode* node = nodeT_create(key, value);
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
            printf("There is already a equal key,please input another key.\n");
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
    return NULL;
}


int bst_remove(void* key, Tree* tree){
    BSTNode* parents = NULL;
    BSTNode* targetn = bst_find(key, tree, &parents); 
    if(targetn == NULL) return 0; 
    int isHead = (parents == NULL);
    int choose = isHead ? 0 : tree->cmpFunc(parents->key, key);

    //childless
    if(targetn->left == NULL && targetn->right == NULL){
        if(!isHead){
            if(choose > 0) parents->left = NULL;
            else parents->right = NULL;
        }else tree->head = NULL;
        node_free(targetn);
    }else if(targetn->left == NULL){        //only child
        if(!isHead){
            if(choose > 0) parents->left = targetn->right;
            else parents->right = targetn->right;
        }else tree->head = targetn->right;
        node_free(targetn);
    }else if(targetn->right == NULL){
        if(!isHead){
            if(choose > 0) parents->left = targetn->left;
            else parents->right = targetn->left;
        }else tree->head = targetn->left;
        node_free(targetn);
    }else{    
        BSTNode* minParents, * minLeft;
        minLeft = targetn->right;
        minParents = targetn;
        while(minLeft->left){
            minParents = minLeft;
            minLeft = minLeft->left;
        }

        targetn->key = minLeft->key;
        targetn->value = minLeft->value;
        if(minParents == targetn){
            targetn->right = minLeft->right;
        }else{
            minParents->left = minLeft->right;
        }
        node_free(minLeft);
    }
    tree->size--; 
    return 1;
}//There are three cases: childless, only child and gemini.


void bst_destroyn(BSTNode* node, free_func free){
    if(node->left){
        bst_destroyn(node->left, free);
    }
    if(node->right){
        bst_destroyn(node->right, free);
    }
    free(node->key);
    free(node->value);
    free(node);
    return;
}//free()

void bst_destroy(Tree* tree, free_func free){
    bst_destroyn(tree->head, free);
    free(tree);
    return;
}

int BSTmode(void){


    WINDOW* win = newwin(MAX_Y, MAX_X, 0, 0);

    Tree* tree = bst_create(int_cmp);
    bst_insert(random_val(), tree, random_char());

    draw_bst(tree, win);

    while(1){
        switch(wgetch(win)){
            case 'i':
                bst_insert(random_val(), tree, random_char());
                break;
            case 'd':
                if(tree->head == NULL) break;
                mvwprintw(win, 25, 0, "Input key:");
                char buf[7];
                wgetnstr(win, buf, 6);  
                int key = atoi(buf);
                while(!(bst_remove(&key, tree))){
                    mvwprintw(win, 24, 0, "There is not this node,please reenter.");
                    mvwprintw(win, 25, 0, "Input key:");
                    wgetnstr(win, buf, 6);  
                    key = atoi(buf);
                }
                break;
            case 'q':
                bst_destroy(tree, node_free);
                delwin(win);
                endwin();
                return 1;
            default:
                break;         
        }
        draw_bst(tree, win);
    }
    return 0;
}
