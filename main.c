//
//  main.c
//  GL_game
//
//  Created by Arnau Sastre on 11/10/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "test1.h"

int main(int argc, const char * argv[]) {
    // insert code here...

    initscr();            /* Start curses mode           */
    

    typedef struct {
    int alive ;
    int pos_x;
    int pos_y; } cell;
    
    
    int fsize = 20;
    
    cell ** field = (cell **) malloc(fsize * sizeof(cell *));
    
    for (int i = 0; i < fsize; ++i)
        field[i] = (cell *)malloc(fsize * sizeof(cell));
    
    
    /*field [0][0].alive = 1;
    field [0][0].pos_x = 1;
    field [0][0].pos_y = 1;

    printw("My cell at 0,0 is at state: %d\n", field[0][0].alive);
    printw("My coordinates for cell at 0,0 are: %d,%d\n",field [0][0]. pos_x , field [0][0]. pos_y );*/
    


    
    //INIT CELL Matrix
    /*for (int i = 0; i<fsize; ++i){
        for (int j = 0; j<fsize; ++i){
            field[i][j].pos_x=1;
            field[i][j].pos_y=1;
            field[i][j].alive=0;
        }
    }*/
    
    printw("Hello World !!!\n");
    addch(ACS_CKBOARD);
    int d = hello();
    printw("x equals %i",d);
    
    refresh();            /* Print it on to the real screen */
    getch();            /* Wait for user input */
    
    
    
    endwin();           /* End curses mode          */
    
    return 0;
}

