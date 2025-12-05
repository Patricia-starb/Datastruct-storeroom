#ifndef VISUAL_H

#define VISUAL_H

#include "list.h"
#include <ncurses.h>
#include "bst.h"
#define MAX_Y 60
#define MAX_X 150

int draw_list(List*, WINDOW*);
void* random_val(void);
void draw_Tnode(BSTNode* , WINDOW*, int, int, int);
void draw_bst(Tree*, WINDOW*);
void* random_char(void);
void animation_draw(WINDOW*, Node*, int, int, int);

#endif