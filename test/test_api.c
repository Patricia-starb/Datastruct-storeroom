#include "bst.h"
#include "list.h"
#include "visual.h"
#include "ds_common.h"
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int main(void){
    initscr();
    noecho();
    cbreak();
    srand(time(NULL));
    int running = 1,infer = 0;
    // enum DSMode { TREE, LIST, QUIT };
    // enum DSMode mode = LIST;
    while(running){
        clear();
        mvprintw(0, 0, "Please select a mode,\'L\' or \'T\',\'q\' to quit:");
        if(infer){
            mvprintw(1, 0, "Please enter valid char! ");
            move(0, 44);
        }
        refresh();
        switch(getch()){
            case 'L':
            case 'l':
                LISTmode();
                break;
            case 'T':
            case 't':
                BSTmode();
                break;
            case 'q':
            case 'Q':
                running = 0;
                break;
            default:
                infer = 1;
                break;
        }

    }
    endwin();
    return 0;
}