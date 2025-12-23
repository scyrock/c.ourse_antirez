#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define SUDOKU_L 3
#define SUDOKU_S 9
#define SUDOKU_DIM SUDOKU_S*SUDOKU_S
#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_RESET    "\x1b[0m"

#define SD_OK 1
#define SD_ERR 0

#include "cellctrl.h"
#include "sudokuhl.h"

typedef struct{
    int value;          // Cell assigned value (0 if unknown)
    bool given ;        // True if the value is given
}sd_cell;

typedef sd_cell sd_grid[SUDOKU_S][SUDOKU_S];
typedef sd_grid* sd_grid_ptr;

/* ---------------------------- Initialization ------------------------------ */

/* Initialize sudoku structure, using standard notation.*/
void init_sudoku(sd_grid_ptr s){
    //char sudoku_in[SUDOKU_DIM+1] = "400060001020038000310004050500000000038000709000000003000010875006903000700020000";
    // char sudoku_in[SUDOKU_DIM+1] = "200900007805147002730208100679301500001589206580670031150402098427000605960015400";
    // char sudoku_in[SUDOKU_DIM+1] = "000031000040702009000090002000000600090008010120070090700000900006400005250000000";
    // char sudoku_in[SUDOKU_DIM+1]= "001000008800009001500030000900008000070200000000750002000000097400076030030000040";
    char sudoku_in[SUDOKU_DIM+1]= "009000050300000801000062003600100700000070006003040100200000480005003000001090000";
    printf("The solved sudoku is: \nhttps://sudoku.coach/en/play/%s\n\n",
           sudoku_in);

    int row = 0;
    int col = 0;
    for(int i=0; i<SUDOKU_DIM; i++){
        row = i/SUDOKU_S;
        col = i%SUDOKU_S;
        (*s)[row][col].value = (int)sudoku_in[i]-'0';
        if((*s)[row][col].value==0) (*s)[row][col].given = false;
        else (*s)[row][col].given = true;
    }
}

/* ------------------------------- Display --------------------------------- */

/* Display the sudoku scheme */
void display_sd(sd_grid_ptr s){
    int row = 0;
    int col = 0;
    separation_line();
    for(row=0; row<SUDOKU_S; row++){
        printf("|");
        for(col=0; col<SUDOKU_S; col++){
            if((*s)[row][col].value != 0){
                if((*s)[row][col].given != 0){
                    printf("%s%d%s", ANSI_COLOR_RED,(*s)[row][col].value,
                           ANSI_COLOR_RESET);
                } else{
                    printf("%d",(*s)[row][col].value);
                }
            }else{
                printf(" ");
            }
            if((col+1)%SUDOKU_L == 0) printf("|");
        }
        printf("\n");
        if((row+1)%SUDOKU_L == 0) separation_line();
    }
}

/* ------------------------------ Helpers ----------------------------------- */

/* Given a cell and a candidate evaluate if the candidate is valid. */
int valid_cand(const sd_grid_ptr s, int row, int col, int num){
    // Check row
    for(int i=0; i<SUDOKU_S; i++){
        if ((*s)[row][i].value==num) return 0;
    }

    // Check column 
    for(int i=0; i<SUDOKU_S; i++){
        if ((*s)[i][col].value==num) return 0;
    }

    // Check square
    int col0 = (col/SUDOKU_L)*SUDOKU_L;
    int row0 = (row/SUDOKU_L)*SUDOKU_L;
    for(int i=0; i<SUDOKU_L; i++){
        for(int j=0; j<SUDOKU_L; j++){
            if((*s)[row0+i][col0+j].value==num) return 0;
        }
    }

    return 1;
}


/* Evaluate the next not given cell. Returns -1 if the actual scheme is ended.
 * NOTE: to evalute the rist cell use col = -1. */
int next_cell(const sd_grid_ptr s, int *row, int *col){
    while(1){
        (*col)++;  // go to next column
        // if out of column number move to the next row
        if(*col>=SUDOKU_S){
            *col = 0;
            (*row)++;
        }
        // Out of the grid
        if(*row>=SUDOKU_S) return SD_ERR;

        /* If the current cell value is not given and is different from zero,
         * the current sudoku state is inconsistent. */
        assert(!((*s)[*row][*col].given==false && (*s)[*row][*col].value!=0));

        // If the current cell value is not given and is zero, return it.
        if((*s)[*row][*col].given==false &&
            (*s)[*row][*col].value==0) return SD_OK;
    }
}

/* Evaluate the previous not given cell. Returns -1 if the actual 
 * scheme is ended */
int prev_cell(const sd_grid_ptr s, int *row, int *col){
    while(1){
        (*col)--;  // go to prev column
        // if out of column number move to the previous row
        if(*col<0){
            *col = SUDOKU_S-1;
            (*row)--;
        }
        // Out of the grid
        if(*row<0) return SD_ERR;

        // If the current cell value is not given, return it.
        if((*s)[*row][*col].given==false) return SD_OK;
    }
}

int next_cand(const sd_grid_ptr s, const int *row, const int *col, int *val){
    while (1) {
        (*val)++;
        if(*val>SUDOKU_S) return SD_ERR;    // check if value is over the bound
        // if the cadidate is valid for the cell, return
        if(valid_cand(s, *row, *col, *val)) return SD_OK;
    }
}

int completed(const sd_grid_ptr s, const int *row, const int *col){
    int row_in = *row;
    int col_in = *col;
    if(!(next_cell(s, &row_in, &col_in)) && (*s)[*row][*col].value!=0)
        return SD_OK;
    return SD_ERR;
}
/* ------------------------------ Sudoku solve ------------------------------ */

int solve(sd_grid_ptr s){
    int row = 0;
    int col = -1;
    int row_in, col_in;
    int iteration = 0;
    int val = 0;

    next_cell(s, &row, &col);

    while(1){
        usleep(50000);
        row_in = row;
        col_in = col;
        iteration++;
        printf("Iteration %d - [Row: %d Column: %d Value: %d]\n",
               iteration, row, col, val);
        val = (*s)[row][col].value;
        display_sd(s);
        if(next_cand(s, &row, &col, &val)){
            (*s)[row][col].value = val;
            next_cell(s, &row, &col);
        }else{
            (*s)[row_in][col_in].value = 0; 
            prev_cell(s, &row, &col);
        }
        if(completed(s, &row, &col)) return SD_OK;
    }
}
int main(void){ 
    sd_grid sudoku;
    init_sudoku(&sudoku);
    solve(&sudoku);
    display_sd(&sudoku);
    return 0;
}
