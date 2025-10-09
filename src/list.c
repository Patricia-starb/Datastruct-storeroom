#include "list.h"
#include <stdio.h>
#include "ds_common.h"
#include <stdlib.h>

List* list_create(){
    List* first = (List*)malloc(sizeof(List));
    first->head = NULL;
    first->size =0;
    return first;
}

Node* node_create(void* val){
    Node* med = (Node*)malloc(sizeof(Node));
    med->data = val;
    med->front = NULL;
    med->back = NULL;
    return med;
}

void flist_insert(List* list, void* val){
    Node* insert = node_create(val);
    if(list->head == NULL){
        list->head = insert;
        insert->front = NULL;
        insert->back = NULL;
    }else{
        Node* medium;
        medium = list->head->back;
        insert->back = medium;
        insert->front = list->head;
        list->head->back = insert;
    }
}

void blist_insert(List* list, void* val){
    Node* insert = node_create(val);
    if(list->head == NULL){
        list->head = insert;
        insert->front = NULL;
        insert->back = NULL;
    }else{
        Node* medium;
        medium = list->head;
        while(medium->back != NULL){
            medium = medium->back;
        }
        medium->back = insert;
        insert->front = medium;
        insert->back = NULL;
    }
}

Node* list_find(List* list, void* val, cmp_func cmp){
    Node* medium = list->head;
    while(medium != NULL){
        if(cmp(medium->data, val) == 0)
            return medium;
        medium = medium->back;
    }
    return NULL;    
}

void list_remove(List* list, void* val, cmp_func cmp, free_func free){
    Node* cur = list_find(list, val, cmp);
    if(cur->front == NULL){
        cur->back->front = cur->front;
        free(cur);
        return;
    }else if(cur->back == NULL){
        cur->front->back = cur->back;
        free(cur);
        return;
    }
    cur->front->back = cur->back;
    cur->back->front = cur->front;
    free(cur);
}

void list_destroy(List* list, free_func free){
    Node* cur = list->head;
    Node* medium;
    while(cur != NULL){
        medium = cur->back;
        free(cur);
        cur = medium;
    }
    free(list);
}