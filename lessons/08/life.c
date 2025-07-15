#include <stdio.h>
/*
 * For firther information about Conway's Game of Life check the wikipedia page:
 * https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 */

/*
 * The apporach used to develop the program is the following:
 * First of all basic funciton are created to handle specilized high level trasks.
 * After these functions are combined to solve the problem.
 */

/*
 * unistd.h library allow to use sleep function, to pause the program exectution
 * for a predefined time.
 */
#include <unistd.h>

/*
 * define allow to store value that are used by the progeam.
 * Each time the preprocessor will find the define variable, will substitute the
 * variable with its value. (eg all COLS will replaced with 25).
 * In GRID_CELLS parentesis are used to endure that, when the define variable 
 * is replaced in the code, the operation sequnce is preserved.
 */
#define GRID_COLS 20                        // Grid columns number
#define GRID_ROWS 20                        // Grid rows number
#define GRID_CELLS (GRID_COLS*GRID_ROWS)    
#define ALIVE '*'                           // Alive symbol
#define DEAD '.'                            // Dead symbol

/*
 * The function convert (x,y) coordinate to its index.
 * The function implement wrapping: value out of the inverval 0 to GRID_COLS/GRID_ROWS
 * are wrapped inside the allowed bounds.
 */
int xy_to_index(int x, int y){
    /*
     * If x or y are smaller than 0 firstly they are converted to positive intager,
     * than the division remainder is computed by %, and finally the value is wrapped
     * to the maximum allowed value.
     */
    if(x<0){
        x = (-x) % GRID_COLS;
        x = GRID_COLS - x;
    }
    if(y<0){
        y = (-y) % GRID_ROWS;
        y = GRID_ROWS - y;
    }

    /*
     * If the value is bigger than grid dimention, the remainder is computed.
     */
    if(x>=GRID_COLS) x = x % GRID_COLS;
    if(y>=GRID_ROWS) y = y % GRID_ROWS;
    
    return y*GRID_COLS+x;    
}
/*
 * The function recives the grid pointer, and change the status of the cell
 * in position (x,y) to state.
 * It is worth to notice that the function operate on the grid pointer, this
 * means that directly modify the argument variable, without returning an output.
 */
void set_cell(char *grid, int x, int y, char state){
    grid[xy_to_index(x,y)] = state;
}

/*
 * The function return the state of grid in position (x,y).
 */
char get_cell(char *grid, int x, int y){
    return grid[xy_to_index(x,y)];
}

/*
 * Display the grid status on the terminal.
 */
void print_grid(char *grid){
    /*
     * Two nested loop allow to print the grid status.
     * After each row, new line command is povided.
     */
    printf("\x1b[H\x1b[2J\x1b[3J"); // clean terminal (clear | hexdump -C)
    for(int y=0 ; y<GRID_ROWS ; y++){
        for(int x=0 ; x<GRID_COLS ; x++){
            printf("%c", get_cell(grid,x,y));
        }
        printf("\n");
    }
}

/*
 * Return the number of living cells around (x,y) position.
 */
int count_living_near(char *grid, int x, int y){
    /*
     * The two nested loop generate all the offset combination.
     * (x+dx,y+dy) access to all the cells near the target cell (x,y).
     * If both offset are zero, the check is skipped, because the state of the 
     * cell itself is not take into account in the game.
     */
    int alive = 0;
    for(int dy=-1;dy<=1;dy++){
        for(int dx=-1;dx<=1;dx++){
            if (dx==0 && dy == 0) continue;
            if (get_cell(grid,x+dx,y+dy)==ALIVE) alive++;
        }
    }
    return alive;
}
/*
 * Set all the grid cells to a given value.
 */
void set_grid(char *grid, char state){
    for(int y=0 ; y<GRID_ROWS ; y++){
        for(int x=0 ; x<GRID_COLS ; x++){
            set_cell(grid,x,y,state);
        }
    }
}

/*
 * The function compute the next state of game of life.
 */
void compute_new_state(char *old, char *new){
    /*
     * All the grid cells are accessed.
     * The number of living cells near to (x,y) is evaluated.
     * By deault the new state is set to DEAD.
     * By nested if condtion it is checked if the requirements to be 
     * ALIVE as next state are fullfilled.
     */
    for(int y=0 ; y<GRID_ROWS ; y++){
         for(int x=0 ; x<GRID_COLS ; x++){
             int n_alive = count_living_near(old,x,y);
             int new_state = DEAD;
             if(get_cell(old,x,y)==ALIVE){
                 if(n_alive==2 || n_alive==3) new_state = ALIVE;
             }else{
                if(n_alive==3) new_state = ALIVE;
             }
             set_cell(new,x,y,new_state);
         }
     }
}
int main(void){
    /*
     * The grid is rapresented by a char array.
     * The value of each cell will be defined by charcters that can be store as
     * char (eg *>alive, .>dead).
     * The grid is not rapresented as a matrix but as an array. Each cell is 
     * univocally identified by its index.
     * 0 1 2 
     * 3 4 5
     * 6 7 8
     * To run the game it is necessary to have at least two grid. The state at the
     * next time instant is funciton of the state at the previous time instant.
     */
    char grid_a[GRID_CELLS];
    char grid_b[GRID_CELLS];
    
    // Set up inital grid state
    set_grid(grid_a,DEAD);

    set_cell(grid_a,10,10,ALIVE);
    set_cell(grid_a,9,10,ALIVE);
    set_cell(grid_a,11,10,ALIVE);
    set_cell(grid_a,11,9,ALIVE);
    set_cell(grid_a,10,8,ALIVE);
    
    set_cell(grid_a,9,3,ALIVE);
    set_cell(grid_a,9,4,ALIVE);
    set_cell(grid_a,9,5,ALIVE);
    
    /*
     * The main loop run until program execution is not terminated (while(1)).
     * 1a. The state of grid_a is printed
     * 2a. Execution wait for 100000 microsecods
     * 3a. Starting from the actual (grid_a) the next state (grid_b) is computed
     * 1b. The state of grid_b is printed
     * 2b. Execution wait for 100000 microsecods
     * 3b. Starting from the actual (grid_b) the next state (grid_a) is computed
     */
    while(1){
        printf(grid_a);
        usleep(100000);
        compute_new_state(grid_a, grid_b);
        print_grid(grid_b);
        usleep(100000);
        compute_new_state(grid_b, grid_a);  
    }

    return 0;
}
