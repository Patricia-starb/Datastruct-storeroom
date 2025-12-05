#include <ncurses.h>
#include "list.h"
#include <unistd.h>
#include <stdlib.h>
#include "bst.h"
#include "visual.h"



// void animation_draw(WINDOW* win, Node* node, int startX, int endX, int y){
//     while(startX != endX){
//         mvwprintw(win, y, startX, "-> [%d]", *(int*)node->data);
//         startX += 2;
//         wrefresh(win);
//         usleep(3000);
//     }
// }

// void remove_node(List* list, void* val, cmp_func cmp, free_func free){
// }

//搁置

int draw_list(List* list, WINDOW* win){
    wclear(win);

    int y,x;
    y = x = 2;
    mvwprintw(win, 0, 0, "List:");
    Node* node = list->head;
    while(node){
        if(x > (MAX_X - 3)){
            y++;x = 2;
        }
        mvwprintw(win, y, x, "[%d]", *(int*)node->data);
        if(node->back){
            mvwprintw(win, y, x+4, "->");
        }
        node = node->back;
        x += 6;
    }
    mvwprintw(win, ++y, 0, "Press \'i\' to insert or \'d\' to delect,\'q\' to quit.");
    if(node && !(list->head->back)) mvwprintw(win, y, 51, "Only a node,don't delect.");
    wrefresh(win);
    return (y+1);
}

void draw_Tnode(BSTNode* node, WINDOW* win, int y, int x, int span){
    if(x < 0 || x > (MAX_X-4) || y > MAX_Y || !node) return;

    mvwprintw(win, y, x, "[%c]", *(char*)node->value);
    mvwprintw(win, y+1, x, "{%d}", *(int*)node->key);

    if(node->left){
        // mvwprintw(win, y+2, x-(span/2), "/");
        draw_Tnode(node->left, win, (y+3), (x-span), (span / 2) == 0 ? 1 : (span / 2));
    }
    if(node->right){
        //mvwprintw(win, y+2, x+(span/2), "\\");
        draw_Tnode(node->right, win, (y+3), (x+span), (span / 2) == 0 ? 1 : (span / 2));
    }
    return;
}

void draw_bst(Tree* tree, WINDOW* win){
    wclear(win);   
    mvwprintw(win, 0, 0, "BST Tree:");
    if(tree->head){
        draw_Tnode(tree->head, win, 4, MAX_X / 2, MAX_X / 4);
        mvwprintw(win, 1, 0, "Press \'i\' to insert or \'d\' to delect,\'q\' to quit.");
        if(!(tree->head->left) && !(tree->head->right)) mvwprintw(win, 2, 0, "Only a node,don't delect.");
    }else mvwprintw(win, 3, 0, "Tree head is void.");
    wrefresh(win);
    return;
}

void* random_val(void){
    int* val = (int*)malloc(sizeof(int));
    *val = rand() % 100;
    return val;
}

void* random_char(void){
    int offset = rand() % 26;
    char* ch = (char*)malloc(sizeof(char));
    if(rand()%2){
        *ch = ('A' + offset);
    }else{
        *ch = ('a' + offset);
    }
    return ch;    
}

