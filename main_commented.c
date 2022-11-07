/*////////////////////
// GAME OF LIFE //////
/////////////////////*/

/*////////////////////////////////
CODER1: Narfi99
CODER2: GLADIS-Kernel
CODER3: MCV1958
////////////////////////////////*/

/*////////////////////////////////
 TEAMWORK STRATEGY:
Work to be done divided in equal parts for each coder:
two coders (1 & 3) did the user interface of the game
which was the most complex part of the algorithm
(window, screen print, keyboard events, etc.) and the
last coder (coder 2) applied the logic of the Game of Life.
////////////////////////////////*/

/* INCLUDE LIBRARIES */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
/* ///////////////// */

/* GLOBAL VARIABLES DECLARATION */
enum { Dead = 0, Live };    //  Status of the cell
int running=1;              //  Status of the algorithm (initially is running)
int size=30;                //  Size of the grid
char **m = NULL;            //  Map where cells are displayed
int px, py;                 //  Position of the cursor (X,Y)
WINDOW *wui;                //  Window where game is displayed
int pau = 1;                //  Status of the game (initially is paused)
long population=0;          //  Cell population counter
long step=0;                //  Steps counter (Generations counter)
/* //////////////////////////// */

/* GAME INITIALIZATION & SETUP (CODER 1) */
void init(void) {
    /*   ncurses.h setup    */
    initscr();              // Initialize ncurses.h
    noecho();               // Switch off echoing of characters in the terminal
    raw();                  // Set raw mode (flow control characters are ignored)
    keypad(stdscr, TRUE);   // Enable user's keypad
    nodelay(stdscr, TRUE);  // Disable block during read (getch)
    curs_set(FALSE);        // Set invisible cursor mode
    start_color();          // Start using colors
    clear();                // Clear the screen
    /* ////////////////////// */

    /* Set pair of window colors */
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);
    /* ///////////////////////// */

    /* Creation of a new window */
    wui = newwin(1, COLS, LINES - 1, 0);    // Declare new window with size (COL,LINES-1)
    wmove(wui, 0, 0);                       // Set window position at (0,0)
    wrefresh(wui);                          // Output the previous window
    refresh();                              // Update the terminal output
    /* ///////////////////////// */

    /* Set initial cursor position */
    px = py = size / 2;     // Set cursor in the middle of the window (X/2,Y/2)
    /* /////////////////////////// */

    /* Creation and allocation of the map m (m is a 2D matrix) */
    int i;                                                                    // Counter i
    m = calloc(size + 1, sizeof(char *));                                     // Allocate (size + 1) * characters
    for(i = 0; i < size + 1; ++i) m[i] = calloc((size*3) + 1, sizeof(char));  // Allocate ((size*3)+1) characters in each previous allocated characters
    /* //////////////////////////////////// */
    return;
}
/*////////////////////////////  */

/* USER INTERFACE (CELLS) (CODER 1) */
void UI(void){
    int i, j;                                                   // Declaration of counters i and j
    for(i=0;i<size;++i){
        for(j=0;j<(size*3);++j){                                //
            attron(m[i][j] ? COLOR_PAIR(2) : COLOR_PAIR(3));    // Turn on attributes of the window. Set pair of color 2 in alive cells, nº3 in dead cells
            if(py == i && px == j){                             //
                attron(COLOR_PAIR(1));                          // Set pair of colors 1 in the cell where the cursor is
            }                                                   //
            mvaddstr(i, j, "0");                                // Set 0 in the position (i,j)
            attroff(m[i][j] ? COLOR_PAIR(2) : COLOR_PAIR(3));   // Turn off attributes of the window
        }
    }
     refresh();                                                 // Update terminal output
     return;
}
/* ////////////////////// */

/* GAME OF LIFE LOGIC (CODER 2) */
void neighbours(void) {
    if(pau) return;         // If the game is paused, return
    int i,j,n=0;            // Declaration of variables (i and j are counters, n is the number of neighbours)
    int a,b;                // Declaration of counters

    /* Creation and allocation of a new map (2D matrix) */
    char **new_m = NULL;                                         // Declare a new map
    new_m = calloc(size + 1, sizeof(char *));                    // Allocate (size+1) characters
          for(i = 0; i < size + 1; ++i)
              new_m[i] = calloc((size * 3) + 1, sizeof(char));   // Allocate (size*3)+1 characters in eache previous allocated characters
    /* //////////////////////////////////////////////// */

    /* Logic */
    for(i = 1; i < size; ++i){
        for(j = 1; j < (size); ++j){
            n=-(m[i][j]);                       // Remove the value of the cell
            for(a = -1; a < 2; ++a){            //
                for(b = -1; b < 2; ++b){        //
                    if(m[i + a][j + b]) ++n;    // Count the amount of neighbours n of a cell located at (i,j)
                            }                   //
                         }                      //
            if(n==2) {new_m[i][j]= m[i][j];}    // If there are 2 neighbours, the cell state does not change
            else if(n==3){new_m[i][j] = Live;}  // If there are 3 neighbours, the cell becomes live
            else{new_m[i][j] = Dead;}           // If there are less than 2 or more than 3 neighbours, the cell becomes dead
        }
    }
    /* ///// */

    ++step;          // One step more done (one new generation created)

    /* Count the population */
    population=0;                                           // Initialize the population variable (amount of alive cells)
    for(i=0;i<size;++i){
        for(j=0;j<(size*3);++j){
        population += ((m[i][j] = new_m[i][j])) ? 1 : 0;    // Count the alive population (amount of alive cells)
        }
    }
    /* /////////////////// */

    /* Deallocation of the map */
    do {
        for(i = 0; i < size; ++i)
            free(new_m[i]);                     //
            free(new_m);                        // Deallocate the cells from the map new_m
            new_m = NULL;                       //
            } while(/* CONSTCOND */ 0);
    /* /////////////////////// */

    usleep(1000000);                            // Wait 1 second
}
/* ////////////////// */

/* SETUP OF THE KEYBOARD EVENTS (CODER 3)*/
void keyboard(void){
    int i, j, c;            // Declaration of variables (i and j are counters, c is the pressed key)
    switch((c = getch()))   // Waits the user interaction with the keyboard and gets the key
    {
    case KEY_UP:                        // If up arrow is pressed, cursor moves up
        if(py > 0)                      // Check if the cursor is below the superior bounder of the window
            --py;                       // Then, subtract 1 from py (Y cursor position)
        break;                          // End for case KEY_UP

    case KEY_DOWN:                      // If down arrow is pressed, cursor moves down
        if(py < size - 1)               // Check if the cursor is over the inferior bounder of the window
            ++py;                       // Then, add 1 to py (Y cursor position)
        break;                          // End for case KEY_DOWN

    case KEY_LEFT:                      // If left arrow is pressed, cursor moves left
        if(px > 0)                      // Check if the cursor is on the right of the left bounder of the window
            --px;                       // Then, subtract 1 from px (X cursor position)
        break;                          // End for case KEY_LEFT

    case KEY_RIGHT:                     // If right arrow is pressed, cursor moves right
        if(px < (size*3) - 1)           // Check if the cursor is on the left of the right bounder of the window
            ++px;                       // Then, add 1 to px (X cursor position)
        break;                          // End for case KEY_RIGHT

    case 'q':                           // If Q key is pressed, quites the algorithm
    case 'Q':                           // Does not matter if capital letter key is activated or not
        running = 0;                    // Set algorithm status at 0 (disabled)
        break;                          // End for case Q

    case 'p':                           // If P key is pressed, pauses or engage the game
    case 'P':                           // Does not matter if capital letter key is activated or not
        pau = !pau;                     // Set game status at the opposite status (1 = paused, 0 = engaged)
        break;                          // End for case P

    case 'c':                           // If C key is pressed, cleans the map and restarts the game
    case 'C':                           // Does not matter if capital letter key is activated or not
        for(i = 0; i < size; ++i)       //
            for(j = 0; j < (size); ++j) // Clean the map by setting 0 to all the 2D matrix positions
                       m[i][j] = 0;     //
              pau = 1;                  // Set game status at 1 (restart the games)
              step=0;                   // Reset steps counter (generations counter)
              population=0;             // Reset population counter (cells counter)
        break;                          // End for case C

    case ' ':                           // If Space bar is pressed, set alive or dead to the cell located in the cursor position
        m[py][px] = !m[py][px];         // Reverse the cell status (1 = alive, 0 = dead)
        break;                          // End for case Space bar

    default:                            // If any other key is pressed, do nothing
        break;                          // End for any other key case
    }
    return;
}
/* //////////////////////////// */

/* USER INTERFACE (TEXT) (CODER 3)*/
void text(void){

    wrefresh(wui);                      // Update the window
    werase(wui);                        // Clear the window
    wattron(wui, COLOR_PAIR(0));        // Turn on attributes of the window. Set pair of color 1 to the window

    /* Show status of the game (paused or running)*/
    wattron(wui, COLOR_PAIR(pau ? 5 : 4) | A_BOLD);     // Turn on attributes of the window. Set pair of color 5 if game is running, if not set nº4
    wprintw(wui, pau ? "[PAUSED]  " : "[RUNNING] ");    // Screen as text the status of the game
    wattroff(wui, COLOR_PAIR(pau ? 5 : 4) | A_BOLD);    // Turn off attributes of the window

    /* Show game information */
    wprintw(wui, "Pos: [%.4dx%.4d] (%s)", px, py, ((m[py][px]) ? "Live" : "Dead"));                     // Text status of the cell in the current position of the cursor
    wprintw(wui, "  Keys->  P: Pause/Run    Space: Live/Dead    C: Clear    Q: Quit Navigate:Arrows");  // Text information about the key events
    wprintw(wui, "     Step: %i  Population: %i",step,population);                                      // Text total amount of steps (generations) and population (cells)
    /* ///////////////////// */

    wattroff(wui, COLOR_PAIR(0));       // Turn off attributes of the window
    wrefresh(wui);                      // Update the window

     return;
}
/* ///////////////////// */

/* MAIN ALGORITHM BLOCK (CODER 1 + CODER 2 + CODER 3) */
int main() {
    init();                 // Initialization and setup of the algorithm
    while(running){
        neighbours();       // Application of the Game of Life logic
        keyboard();         // Application of the Keyboard events
        UI();               // Setup of the User Interface
        text();             // Screen information about the game
    }
    endwin();               // Suspension of the ncurses session

    return 0;
}
/* //////////////////// */
