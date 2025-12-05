#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "ds_common.h"
#include "visual.h"
#include <ncurses.h>
#include <time.h>


int main(void){
    initscr();
    noecho();
    cbreak();
    srand(time(NULL));

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
                return 0;
            default:
                break;         
        }
        draw_bst(tree, win);
    }
    return 0;
}


    // BSTNode *node, *parents = NULL;
    // int six = 6;
    // node = bst_find(&six, tree, &parents);
    // printf("key:%d\nvalue:%c\n", *(int*)(node->key), *(char*)(node->value));
    // printf("Tree size:%d\n", tree->size);

    // void** bitArray = (void**)malloc(sizeof(void*) * tree->size);
    // index = 0;
    // bitTree(tree->head, bitArray, &index);
    // printf("Binary inorder traversal:\n");
    // index = 0;
    // while(index < tree->size){
    //     printf(" %d ", *(int*)(bitArray[index]));
    //     index++;
    // }

    // bst_remove(&six, tree);
    // printf("\nTree size:%d\n", tree->size);
    // node_free(bitArray);
    // void** bitArrayNow = (void**)malloc(sizeof(void*) * tree->size);
    // index = 0;
    // bitTree(tree->head, bitArrayNow, &index);
    // printf("Binary inorder traversal now:\n");
    // index = 0;
    // while(index < tree->size){
    //     printf(" %d ", *(int*)(bitArrayNow[index]));
    //     index++;
    // }
    // printf("\n");
    // node_free(bitArrayNow);
