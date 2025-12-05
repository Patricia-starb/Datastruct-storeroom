#include "ds_common.h"
#include "list.h"
#include "visual.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

List* list_create(){
    List* first = (List*)malloc(sizeof(List));
    first->head = NULL;
    first->size =0;
    return first;
}

Node* nodeL_create(void* val){
    Node* med = (Node*)malloc(sizeof(Node));
    med->data = val;
    med->front = NULL;
    med->back = NULL;
    return med;
}

void flist_insert(List* list, void* val){
    Node* insert = nodeL_create(val);
    if(list->head == NULL){
        list->head = insert;
        insert->front = NULL;
        insert->back = NULL;
    }else{
        Node* medium = list->head->back;
        insert->back = medium;
        insert->front = list->head;
        list->head->back = insert;
        if(medium){
            medium->front = insert;
        }
    }
}

void blist_insert(List* list, void* val){
    Node* insert = nodeL_create(val);
    if(list->head == NULL){
        list->head = insert;
        insert->front = NULL;
        insert->back = NULL;
    }else{
        Node* medium = list->head;
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

int list_remove(List* list, void* val, cmp_func cmp, free_func free){
    Node* cur = list_find(list, val, cmp);
    if(!cur) return 0;
    if(cur == list->head){
        list->head = NULL;
        free(cur);
        return 1;
    }
    if(cur->front == NULL){
        cur->back->front = NULL;
        list->head = cur->back;
        free(cur);
        return 1;
    }else if(cur->back == NULL){
        cur->front->back = cur->back;
        free(cur);
        return 1;
    }
    cur->front->back = cur->back;
    cur->back->front = cur->front;
    free(cur->data);
    free(cur);
    return 1;
}

void list_destroy(List* list, free_func free){
    Node* cur = list->head;
    Node* medium;
    while(cur != NULL){
        medium = cur->back;
        free(cur->data);
        free(cur);
        cur = medium;
    }
    free(list);
}

int LISTmode(void){
    
    WINDOW* win = newwin(MAX_Y, MAX_X,0,0);
    List* l = list_create();
    
    flist_insert(l, random_val());

    int y = draw_list(l, win);   
    int running = 1;
    while(running){
        switch(wgetch(win)){
            case 'i':
                mvwprintw(win, y, 0, "Please select insert type front-insert or back-insert(\'f\',\'b\'):");
                if(wgetch(win) == 'f')
                    flist_insert(l, random_val());
                else
                    blist_insert(l, random_val());
                break;
            case 'd':
                if(l->head == NULL) break;
                mvwprintw(win, 4, 0, "Input val:");
                char buf[7];
                wgetnstr(win, buf, 6);  
                int val = atoi(buf);
                while(!(list_remove(l, &val, int_cmp, node_free))){
                    mvwprintw(win, 5, 0, "There is not this node,please reenter.");
                    mvwprintw(win, 4, 0, "Input val:");
                    wgetnstr(win, buf, 6);  
                    val = atoi(buf);
                }

                break;
            case 'q':
                list_destroy(l,node_free);
                delwin(win);
                endwin();
                return 1;
            default: 
                break;
        }
        draw_list(l, win);
    }
    list_destroy(l,node_free);
    delwin(win);
    endwin();
    return 0;

}
