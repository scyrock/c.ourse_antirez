#include <stdio.h>

#define SUDOKU_L 3
#define SUDOKU_S 9 
#define SUDOKU_DIM SUDOKU_S*SUDOKU_S

#include "cellctrl.h"
#include "sudokuhl.h"

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

/* Assign the value if is the only candidate of a cell. */
int naked_cand (sudoku_grid_ptr s){
    for(int row=0; row<SUDOKU_S; row++){
        for(int col=0; col<SUDOKU_S; col++){

            int n = (*s)[row][col].candidate;
            if(only_one_cand(n) && n>0){
                int val = cand_bin2dec(n);
                printf("Naked Candidate: Row %d - Col %d - Value %d\n", 
                        row+1, col+1, val);
                release(s,row,col,val);
                (*s)[row][col].candidate = 0;
                (*s)[row][col].value = val;
                return 1;
            }
        
        }
    }
    return 0;
}

/* Assign a value if is present as a candidate only in a cell of a row. */
int naked_column(sudoku_grid_ptr s){
    for(int col=0; col<SUDOKU_S; col++){
        for(int row_cand=1; row_cand<=SUDOKU_S; row_cand++){
            if(cand_absent_in_row(s,col,row_cand)){
                
                int row_target = row_cand_position(s, col, row_cand);
                if (row_target>=0){
                   printf("Naked Column   : Row %d - Col %d - Value %d\n", 
                           row_target+1, col+1, row_cand);
                   release(s,row_target,col,row_cand);
                   (*s)[row_target][col].candidate = 0;
                   (*s)[row_target][col].value = row_cand;
                   return 1;
                }
            
            }
        }
    }
    return 0;
}

/* Assign a value if is present as a candidate only in a cell of a column. */
int naked_row(sudoku_grid_ptr s){
    for(int row=0; row<SUDOKU_S; row++){
        for(int col_cand=1; col_cand<=SUDOKU_S; col_cand++){
            if(cand_absent_in_col(s,row,col_cand)){

                int col_target = col_cand_position(s, row, col_cand);
                if (col_target>=0){
                   printf("Naked Row      : Row %d - Col %d - Value %d\n", 
                           row+1, col_target+1, col_cand);
                   release(s,row,col_target,col_cand);
                   (*s)[row][col_target].candidate = 0;
                   (*s)[row][col_target].value = col_cand;
                   return 1;
                }
            
            }
        }
    }
    return 0;
}

/* Assign a value if is present as a candidate only in a cell of a block. */
int naked_block(sudoku_grid_ptr s){
    for(int row0=0; row0<SUDOKU_S; row0+=SUDOKU_L){
        for(int col0=0; col0<SUDOKU_S; col0+=SUDOKU_L){
            for(int block_cand=1; block_cand<=SUDOKU_S; block_cand++){
                if(cand_absent_in_block(s,row0,col0,block_cand)){
                    
                    int target[2] = {-1,-1}; 
                    if(block_cand_position(s,row0,col0, block_cand,target)
                            && target[0]>=0 && target[1]>=0){
                        int row_target = target[0];
                        int col_target = target[1];
                        printf("Naked Block    : Row %d - Col %d - Value %d\n", 
                                row_target+1, col_target+1, block_cand);
                        release(s,row_target,col_target,block_cand);
                        (*s)[row_target][col_target].candidate = 0;
                        (*s)[row_target][col_target].value = block_cand;
                        return 1;
                    } 
                
                }
            }
        }
    }
    return 0;
}

/* Applies all naked method to the sudoku and updates the scheme.*/
int solve_sudoku(sudoku_grid_ptr s){

    int updated = 0;
    updated = (naked_cand(s) | updated);
    updated = (naked_column(s) | updated);
    updated = (naked_row(s) | updated);
    updated = (naked_block(s) | updated);

    return updated;
}

int main(void){
    sudoku_grid sudoku;
    init_sudoku(&sudoku);
    display_sudoku(&sudoku);
    candidate(&sudoku);
    int updated = 1;
    
    while(updated) updated = solve_sudoku(&sudoku); 
    display_sudoku(&sudoku);
    return 0;
}
