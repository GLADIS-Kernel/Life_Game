/*////////////////////////////////
GAME OF LIFE
////////////////////////////////*/
/*////////////////////////////////
CODER1: Narfi99
CODER2: GLADIS-Kernel
CODER3: MARCEL COLET
////////////////////////////////*/

//INCLUDE LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>


enum { Dead = 0, Live };    //cell status


int running=1;        //run in the initial
int size=30;        //grid size
char **m = NULL;    //map

int px, py;        //cursor position
WINDOW *wui;

int pau = 1;        //start paused
long population=0;    //Count population
long step=0;        //count steps



void
init(void)
{

    //initialize ncurses
    initscr();
    noecho();
    raw();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(FALSE);
    start_color();
    clear();

    //Colors for the window
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);
    
    //window
    wui = newwin(1, COLS, LINES - 1, 0);
    wmove(wui, 0, 0);
    wrefresh(wui);
    refresh();
    
    //cursor start point
    px = py = size / 2;

    //Map allocation
    int i;
    m = calloc(size + 1, sizeof(char *));
    for(i = 0; i < size + 1; ++i)
        m[i] = calloc((size*3) + 1, sizeof(char));


}


void
UI(void)        //user interface
{
    int i, j, c= 0;
    for(i=0;i<size;++i){
        for(j=0;j<(size*3);++j){
            attron(m[i][j] ? COLOR_PAIR(2) : COLOR_PAIR(3));
            
            if(py == i && px == j){
                attron(COLOR_PAIR(1));
            }
            mvaddstr(i, j, "0");
            attroff(m[i][j] ? COLOR_PAIR(2) : COLOR_PAIR(3));
        }
    }
        

     refresh();

     return;
}


void
neighbours(void)
{
    if(pau)
        return;
    
    int i,j,n=0;                //ij table position, n neighbours
    int a,b;                //current cell pos.
    char **new_m = NULL;            //new map
    
                                                
          new_m = calloc(size + 1, sizeof(char *));
          for(i = 0; i < size + 1; ++i)
              new_m[i] = calloc((size * 3) + 1, sizeof(char));

    
    for(i = 1; i < size; ++i){
              for(j = 1; j < (size); ++j){
            n=-(m[i][j]);    //remove the value of the cell
            for(a = -1; a < 2; ++a){        //positions around ij cell
                       for(b = -1; b < 2; ++b){
                            if(m[i + a][j + b]){
                                     ++n;
                                }
                            }
                         }
                        
            
            if(n==2){
                new_m[i][j]= m[i][j];    //not change state
                }
            else if(n==3){
                new_m[i][j] = Live;    //Live
            }
            else{ // <2 underpopulation or >3 overpopulation
                new_m[i][j] = Dead;     //Dead
            }
        }
    }
                    
    ++step;        //one more step done
    
    population=0;
    for(i=0;i<size;++i){
        for(j=0;j<(size*3);++j){
        
        population += ((m[i][j] = new_m[i][j])) ? 1 : 0;
        
        }
    }
    

      do {                        \
              for(i = 0; i < size; ++i) \
                   free(new_m[i]);       \
              free(new_m);               \
              new_m = NULL;              \
         } while(/* CONSTCOND */ 0);
    usleep(1000000);        //delay 1s
}




void
keyboard(void)
{
    int i, j, c;

    //get key from the keyboard
    switch((c = getch()))
    {
    //move cursor up, down, left, right
    case KEY_UP:
        if(py > 0)
            --py;
        break;

    case KEY_DOWN:
        if(py < size - 1)
            ++py;
        break;

    case KEY_LEFT:
        if(px > 0)
            --px;
        break;

    case KEY_RIGHT:
        if(px < (size*3) - 1)
            ++px;
        break;


    case 'q':
    case 'Q':
        running = 0;
        break;


    case 'p':
    case 'P':
        pau = !pau;
        break;


    case 'c':
    case 'C':
        for(i = 0; i < size; ++i) \
            for(j = 0; j < (size); ++j)
                       m[i][j] = 0;
              pau = 1;
        break;

     /* Reverse selected cells state */
    case ' ':
        m[py][px] = !m[py][px];
        break;



    default:
        break;
    }

    return;
}


void
text(void)
{

    //window
    wrefresh(wui);
    werase(wui);
    wattron(wui, COLOR_PAIR(0));

    
    //info running or paused
    wattron(wui, COLOR_PAIR(pau ? 5 : 4) | A_BOLD);
    wprintw(wui, pau ? "[PAUSED]  " : "[RUNNING] ");
    wattroff(wui, COLOR_PAIR(pau ? 5 : 4) | A_BOLD);

    //info for current position
    wprintw(wui, "Pos: [%.4dx%.4d] (%s)", px, py, ((m[py][px]) ? "Live" : "Dead"));
    //Key info
    wprintw(wui, "        Keys->  P: Pause/Run    Space: Live/Dead    C: Clear    Q: Quit        Arrows: Up/Down/Left/Right");
    

    wattroff(wui, COLOR_PAIR(0));

/*////////////////////////////
AÑADIR UNA LINEA DEBAJO QUE PONGA EL STEP Y LA POPULATION
////////////////////////////*/


    wrefresh(wui);

     return;
}



    

int main()
{
    init();
    
    while(running){
    neighbours();
    keyboard();
    UI();
    text();
    }
    
    endwin();

    return 0;
}
    
