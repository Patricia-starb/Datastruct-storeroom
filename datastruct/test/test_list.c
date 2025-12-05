#include "ds_common.h"
#include "list.h"
#include "visual.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

int main(void){
    initscr();
    noecho();
    cbreak();
    srand(time(NULL));
    
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
                return 0;
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