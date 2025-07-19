#include <stdio.h>
/*
 * For further information about Conway's Game of Life check the wikipedia page:
 * https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 */

/*
 * The approach used to develop the program is the following:
 * First of all basic functions are created to handle specialized high level tasks.
 * After these functions are combined to solve the problem.
 */

/*
 * unistd.h library allows to use sleep function, to pause the program execution
 * for a predefined time.
 */
#include <unistd.h>

/*
 * define allows to store values that are used by the program.
 * Each time the preprocessor will find the define variable, it will substitute the
 * variable with its value. (e.g. all COLS will be replaced with 25).
 * In GRID_CELLS parentheses are used to ensure that, when the define variable
 * is replaced in the code, the operation sequence is preserved.
 */
#define GRID_COLS 20                        // Grid columns number
#define GRID_ROWS 20                        // Grid rows number
#define GRID_CELLS (GRID_COLS*GRID_ROWS)    
#define ALIVE '*'                           // Alive symbol
#define DEAD '.'                            // Dead symbol

/*
 * The function converts (x,y) coordinate to its index.
 * The function implements wrapping: values out of the interval 0 to GRID_COLS/GRID_ROWS
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
     * If the value is bigger than grid dimension, the remainder is computed.
     */
    if(x>=GRID_COLS) x = x % GRID_COLS;
    if(y>=GRID_ROWS) y = y % GRID_ROWS;
    
    return y*GRID_COLS+x;    
}

/*
 * The function receives the grid pointer, and changes the status of the cell
 * in position (x,y) to state.
 * It is worth to notice that the function operates on the grid pointer, this
 * means that it directly modifies the argument variable, without returning an output.
 */
void set_cell(char *grid, int x, int y, char state){
    grid[xy_to_index(x,y)] = state;
}

/*
 * The function returns the state of grid in position (x,y).
 */
char get_cell(char *grid, int x, int y){
    return grid[xy_to_index(x,y)];
}

/*
 * Display the grid status on the terminal.
 */
void print_grid(char *grid){
    /*
     * Two nested loops allow to print the grid status.
     * After each row, new line command is provided.
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
 * Returns the number of living cells around (x,y) position.
 */
int count_living_near(char *grid, int x, int y){
     /*
     * The two nested loops generate all the offset combinations.
     * (x+dx,y+dy) accesses to all the cells near the target cell (x,y).
     * If both offsets are zero, the check is skipped, because the state of the
     * cell itself is not taken into account in the game.
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
 * Sets all the grid cells to a given value.
 */
void set_grid(char *grid, char state){
    for(int y=0 ; y<GRID_ROWS ; y++){
        for(int x=0 ; x<GRID_COLS ; x++){
            set_cell(grid,x,y,state);
        }
    }
}

/*
 * The function computes the next state of game of life.
 */
void compute_new_state(char *old, char *new){
    /*
     * All the grid cells are accessed.
     * The number of living cells near to (x,y) is evaluated.
     * By default the new state is set to DEAD.
     * By nested if condition it is checked if the requirements to be
     * ALIVE as next state are fulfilled.
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
     * The grid is represented by a char array.
     * The value of each cell will be defined by characters that can be stored as
     * char (e.g. *>alive, .>dead).
     * The grid is not represented as a matrix but as an array. Each cell is
     * univocally identified by its index.
     * 0 1 2
     * 3 4 5
     * 6 7 8
     * To run the game it is necessary to have at least two grids. The state at the
     * next time instant is function of the state at the previous time instant.
     */
    char grid_a[GRID_CELLS];
    char grid_b[GRID_CELLS];
    
    // Set up initial grid state
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
     * The main loop runs until program execution is not terminated (while(1)).
     * 1a. The state of grid_a is printed
     * 2a. Execution waits for 100000 microseconds
     * 3a. Starting from the actual (grid_a) the next state (grid_b) is computed
     * 1b. The state of grid_b is printed
     * 2b. Execution waits for 100000 microseconds
     * 3b. Starting from the actual (grid_b) the next state (grid_a) is computed
     */
    while(1){
        print_grid(grid_a);
        usleep(100000);
        compute_new_state(grid_a, grid_b);
        print_grid(grid_b);
        usleep(100000);
        compute_new_state(grid_b, grid_a);  
    }

    return 0;
}
