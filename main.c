//
//  main.c
//  GL_game
//
//  Created by Arnau Sastre on 11/10/22.
//

#include <stdio.h>
#include <ncurses.h>
#include "test1.h"

int main(int argc, const char * argv[]) {
    // insert code here...

    initscr();            /* Start curses mode           */
    
    struct cell {
        int alive;
        int pos_x;
        int pos_y;
        
    };
    
    int width = 50;
    int height = 50;
    
    
    struct cell c1; // declares two cell variables // of type stru
    c1.pos_x = 30; // sets x coordinate of cell 1 to 30
    c1.pos_y = 50; // sets x coordinate of cell 1 to 50
    c1.alive = 1; // cell 1 is alive
    
    
    printw("Hello World !!!");    /* Print Hello World          */
    int d =hello();
    printw("%i",d);
    printw("%i",c1.pos_x);
    refresh();            /* Print it on to the real screen */
    getch();            /* Wait for user input */
    endwin();           /* End curses mode          */
    
    return 0;
}
