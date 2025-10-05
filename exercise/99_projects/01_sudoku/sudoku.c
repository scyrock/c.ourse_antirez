#include <stdio.h>

#define SUDOKU_L 3
#define SUDOKU_S 9 
#define SUDOKU_DIM SUDOKU_S*SUDOKU_S

#include "cellctrl.h"
// >>>>> Visualization <<<<<
void separation_line(void){
    for(int i=0; i<SUDOKU_S; i++){
        if((i%SUDOKU_L)==0) printf("+");
        printf("-");
    }
    printf("+\n");
}

/* Display the sudoku scheme */
void display_sudoku(sudoku_grid_ptr s){
    int row = 0;
    int col = 0;
    separation_line();
    for(row=0; row<SUDOKU_S; row++){
        printf("|");
        for(col=0; col<SUDOKU_S; col++){
            if((*s)[row][col].value != 0){
                printf("%d",(*s)[row][col].value);
            }else{
                printf(" ");
            }
            if((col+1)%SUDOKU_L == 0) printf("|");
        }
        printf("\n");
        if((row+1)%SUDOKU_L == 0) separation_line();
    }
}

/* Print the candidate in binary format. */
void print_binary(int n){
    for(int i=SUDOKU_S; i>0; i--){
        printf("%d", (n >> i) & 1); 
    }
    printf("\n");
}

// >>>>> Initialization <<<<<
void init_sudoku(sudoku_grid_ptr s){
    
    /* Solvable */
    // char sudoku_in[SUDOKU_DIM+1] = "400060001020038000310004050500000000038000709000000003000010875006903000700020000";    
    // char sudoku_in[SUDOKU_DIM+1] = "200900007805147002730208100679301500001589206580670031150402098427000605960015400"; 
    char sudoku_in[SUDOKU_DIM+1] = "000031000040702009000090002000000600090008010120070090700000900006400005250000000";
    
    /* Unsolvable */
    // char sudoku_in[SUDOKU_DIM+1]= "001000008800009001500030000900008000070200000000750002000000097400076030030000040";
    printf("The solved sudoku is: \n https://sudoku.coach/en/play/%s\n", sudoku_in); 
    int row = 0;
    int col = 0;
    for(int i=0; i<SUDOKU_DIM; i++){
        row = i/SUDOKU_S;
        col = i%SUDOKU_S;
        (*s)[row][col].value = (int)sudoku_in[i]-'0';
    }
}

/* Given a cell and a candidate evaluate if the candidate is valid. */
int valid_candidate(sudoku_grid_ptr s, int row, int col, int num){ 
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

/* Evaluate the valid candidate of the sudoku.*/
void candidate(sudoku_grid_ptr s){
    for(int row=0; row<SUDOKU_S; row++){
        for(int col=0; col<SUDOKU_S; col++){
            (*s)[row][col].candidate = 0;
            if((*s)[row][col].value == 0){
                // printf("Row %d, Col %d - ",row+1,col+1);
                for(int i=0; i<=SUDOKU_S; i++){
                    if(valid_candidate(s,row,col,i)){
                        // printf("%d  ", i);
                        set_candidate(s,row,col,i);
                    }
                }
                // printf("\n");
                // print_binary((*s)[row][col].candidate);
            }
        }
    }
}

/* Update candidates after a new value is assigned to a cell. */
void release(sudoku_grid_ptr s, int row, int col, int num){
    // Release row
    for(int i=0; i<SUDOKU_S; i++){
        if ((*s)[row][i].value==0) unset_candidate(s,row,i,num);
    }
    // Check column 
    for(int i=0; i<SUDOKU_S; i++){
        if ((*s)[i][col].value==0) unset_candidate(s,i,col,num);
    }
    // Check square
    int col0 = (col/SUDOKU_L)*SUDOKU_L;
    int row0 = (row/SUDOKU_L)*SUDOKU_L;
    // printf("Row %d, Col %d\n", row, col);
    // printf("Row %d, Col %d\n", row0, col0);
    for(int i=0; i<SUDOKU_L; i++){
        for(int j=0; j<SUDOKU_L; j++){
            if((*s)[row0+i][col0+j].value==0) unset_candidate(s,row0+i,col0+j,num);
        }
    }
}

/* Assign the value if is che only candidate of a cell. */
int naked_candidate (sudoku_grid_ptr s){
    for(int row=0; row<SUDOKU_S; row++){
        for(int col=0; col<SUDOKU_S; col++){
            int n = (*s)[row][col].candidate;
            //printf("%d\n\n", (*s)[row][col].candidate);
            if(only_one_candidate(n) && n>0){
                int val = candidate_bin2dec(n);
                //print_binary((*s)[row][col].candidate);
                //printf("%d", (*s)[row][col].candidate);
                printf("Naked Candidate: Row %d - Col %d - Value %d\n", row+1, col+1, val);
                release(s,row,col,val);
                //print_binary((*s)[0][1].candidate);
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
        for(int row_candidate=1; row_candidate<=SUDOKU_S; row_candidate++){
            if(cand_absent_in_row(s,col,row_candidate)){
                int row_target = row_candidate_position(s, col, row_candidate);
                //printf("The returned value of row_candidate_position is: %d\n", row_target);
                if (row_target>=0){
                   //print_binary((*s)[row][col].candidate);
                   //printf("%d", (*s)[row][col].candidate);
                   printf("Naked Column   : Row %d - Col %d - Value %d\n", row_target+1, col+1, row_candidate);
                   release(s,row_target,col,row_candidate);
                   (*s)[row_target][col].candidate = 0;
                   (*s)[row_target][col].value = row_candidate;
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
        for(int col_candidate=1; col_candidate<=SUDOKU_S; col_candidate++){
            if(cand_absent_in_col(s,row,col_candidate)){
                int col_target = col_candidate_position(s, row, col_candidate);
                //printf("The returned value of col_candidate_position is: %d\n", col_target);
                if (col_target>=0){
                   //print_binary((*s)[row][col].candidate);
                   //printf("%d", (*s)[row][col].candidate);
                   printf("Naked Row      : Row %d - Col %d - Value %d\n", row+1, col_target+1, col_candidate);
                   release(s,row,col_target,col_candidate);
                   (*s)[row][col_target].candidate = 0;
                   (*s)[row][col_target].value = col_candidate;
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
            for(int block_candidate=1; block_candidate<=SUDOKU_S; block_candidate++){
                if(cand_absent_in_block(s,row0,col0,block_candidate)){
                    int target[2] = {-1,-1}; 
                    //printf("Row 0 = %d, Col0 = %d, candidate = %d\n", row0, col0, block_candidate);

                    //printf("AAA %d", flag);
                    if(block_candidate_position(s,row0,col0, block_candidate,target)
                            && target[0]>=0 && target[1]>=0){
                        int row_target = target[0];
                        int col_target = target[1];
                        printf("Naked Block    : Row %d - Col %d - Value %d\n", 
                                row_target+1, col_target+1, block_candidate);
                        release(s,row_target,col_target,block_candidate);
                        (*s)[row_target][col_target].candidate = 0;
                        (*s)[row_target][col_target].value = block_candidate;
                        return 1;
                    } 
                }
            }
        }
    }
    return 0;
}

int solve_sudoku(sudoku_grid_ptr s){
    int updated = 0;
    updated = (naked_candidate(s) | updated);
    updated = (naked_column(s) | updated);
    updated = (naked_row(s) | updated);
    updated = (naked_block(s) | updated);
    // printf("Updated: %d\n", updated);
    // print_binary((*s)[2][4].candidate);

    return updated;
}

int main(void){
    sudoku_grid sudoku;
    init_sudoku(&sudoku);
    display_sudoku(&sudoku);
    candidate(&sudoku);
    int updated = 1;
    
    while(updated) updated = solve_sudoku(&sudoku); 
    //updated = solve_sudoku(&sudoku); 
    display_sudoku(&sudoku);
    return 0;
}
