#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUDOKU_L 3
#define SUDOKU_S 9 
#define SUDOKU_DIM SUDOKU_S*SUDOKU_S

#include "cellctrl.h"
#include "sudokuhl.h"

struct bt_node{
    struct bt_node *prev_node;
    sudoku_grid grid;
    int row_g;
    int col_g;
    int val_g;
};

// >>>>> Initialization <<<<<

/* Initialize sudoku structure, using standard notation.*/
void init_sudoku(sudoku_grid_ptr s){
    
    /* Solvable sudoku */
    // char sudoku_in[SUDOKU_DIM+1] = "400060001020038000310004050500000000038000709000000003000010875006903000700020000";    
    // char sudoku_in[SUDOKU_DIM+1] = "200900007805147002730208100679301500001589206580670031150402098427000605960015400"; 
    char sudoku_in[SUDOKU_DIM+1] = "000031000040702009000090002000000600090008010120070090700000900006400005250000000";
    
    /* Unsolvable sudku */
    // char sudoku_in[SUDOKU_DIM+1]= "001000008800009001500030000900008000070200000000750002000000097400076030030000040";
    printf("The solved sudoku is: \nhttps://sudoku.coach/en/play/%s\n\n", sudoku_in); 
    int row = 0;
    int col = 0;
    for(int i=0; i<SUDOKU_DIM; i++){
        row = i/SUDOKU_S;
        col = i%SUDOKU_S;
        (*s)[row][col].value = (int)sudoku_in[i]-'0';
    }
}

/* Given a cell and a candidate evaluate if the candidate is valid. */
int valid_cand(sudoku_grid_ptr s, int row, int col, int num){ 
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

/* Evaluate the valid candidates of the sudoku.*/
void candidate(sudoku_grid_ptr s){
    for(int row=0; row<SUDOKU_S; row++){
        for(int col=0; col<SUDOKU_S; col++){
            (*s)[row][col].candidate = 0;
            if((*s)[row][col].value == 0){
                for(int i=0; i<=SUDOKU_S; i++){
                    if(valid_cand(s,row,col,i)){
                        set_cand(s,row,col,i);
                    }
                }
            }
        }
    }
}

/* Update candidates after a new value is assigned to a cell. */
void release(sudoku_grid_ptr s, int row, int col, int num){
    // Release row
    for(int i=0; i<SUDOKU_S; i++){
        if ((*s)[row][i].value==0) unset_cand(s,row,i,num);
    }
    // Check column 
    for(int i=0; i<SUDOKU_S; i++){
        if ((*s)[i][col].value==0) unset_cand(s,i,col,num);
    }
    // Check square
    int col0 = (col/SUDOKU_L)*SUDOKU_L;
    int row0 = (row/SUDOKU_L)*SUDOKU_L;
    for(int i=0; i<SUDOKU_L; i++){
        for(int j=0; j<SUDOKU_L; j++){
            if((*s)[row0+i][col0+j].value==0) unset_cand(s,row0+i,col0+j,num);
        }
    }
}

struct bt_node *init_bt_node(struct bt_node *prev_bt){
    struct bt_node *new_bt = malloc(sizeof(struct bt_node));
    memcpy(new_bt, prev_bt, sizeof(struct bt_node));
    // Initialize node guesses
    new_bt->row_g = 0;          
    new_bt->col_g = 0;
    new_bt->val_g = 0;
    
    return new_bt;
}
int main(void){
    sudoku_grid sudoku;
    init_sudoku(&sudoku);
    display_sudoku(&sudoku);
    candidate(&sudoku);
    
    display_sudoku(&sudoku);
    return 0;
}
