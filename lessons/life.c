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
 * define allow to store value that are used by the progeam.
 * Each time the preprocessor will find the define variable, will substitute the
 * variable with its value. (eg all COLS will replaced with 25)
 */

#define GRID_COLS = 25   // Grid columns number
#define GRID_ROWS = 25   // Grid rows number
#define ALIVE = '*' // Alive symbol
#define DEAD = '.'  // Dead symbol

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
        y = GRID_ROWS - Y;
    }

    /*
     * If the value is bigger than grid dimention, the remainder is computed.
     */
    if(x>=GRID_COLS) x = x % GRID_COLS;
    if(y>=GRID_ROWS) x = y % GRID_ROWS;
    
    return x*GRID_ROWS+y;    
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
    for(int y=0 ; y<GRID_ROWS ; y++){
        for(int x=0 ; x<GRID_COLS ; x++){
            printf("%c", get_cell(grid,x,y));
        }
        printf("\n");
    }
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
     */
    char grid[GRID_COLS*GRID_ROWS];
    set_grid(grid,ALIVE);
    print_grid(grid);
    return 0;
}
