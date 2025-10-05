typedef struct{
    int value;          // Cell assigne value (0 if unknown)
    int candidate;      // Cell valid candidate stores in binary format 
                           // (1 if valid candidate)
}sudoku_cell;

typedef sudoku_cell sudoku_grid[SUDOKU_S][SUDOKU_S];
typedef sudoku_grid* sudoku_grid_ptr;
   
// Handle all the binary candidate operations. 

/* Set the candidate `value` in position [`row`][`col`] */
void set_cand(sudoku_grid_ptr s,int row, int col, int value){
    (*s)[row][col].candidate |= (1<<value);
}
   
/* Unset the candidate `value` in position [`row`][`col`] */
void unset_cand(sudoku_grid_ptr s, int row, int col, int value){
    (*s)[row][col].candidate &= ~(1<<value);
}

/* Check if `value` is a valid candidate of `candidates`.*/
int is_cand(int candidates, int value){
    if(candidates & (1<<value)) return 1;
    return 0;
}
/* Return true if there is only one allowed candidate.*/
int only_one_cand(int n){
    if ((n & (n - 1)) == 0) return 1;
    return 0;
}

/* Check if a value is a valid candidate in a row.*/
int cand_absent_in_row(sudoku_grid_ptr s, int col, int value){
    for(int row=0; row<SUDOKU_S; row++){
        if((*s)[row][col].value==value) return 0;
    }
    return 1;  
}

/* Check if a value is a valid candidate in a column.*/
int cand_absent_in_col(sudoku_grid_ptr s, int row, int value){
    for(int col=0; col<SUDOKU_S; col++){
        if((*s)[row][col].value==value) return 0;
    }
    return 1;  
}

/* Check if a value is a valid candidate in a its cell.*/
int cand_absent_in_block(sudoku_grid_ptr s, int row0, int col0, int value){
    for(int i=0; i<SUDOKU_L; i++){
        for(int j=0; j<SUDOKU_L; j++){
            if((*s)[row0+i][col0+j].value==value) return 0;
        }
    }
    return 1;  
}
/* Given a column `col` and a taget value `value` return the row `row_target` in 
 * which `val` is a naked candidate. Otherwise return -1. */
int row_cand_position(sudoku_grid_ptr s, int col, int value){
    int row_target = -1;
    for(int row=0; row<SUDOKU_S; row++){
        if(is_cand((*s)[row][col].candidate,value)){     // `value` is candidate
            if(row_target==-1) row_target=row;           // first time in the col
            else return -1;                              // not naked
        } 
    }
    return row_target;
}

/* Given a row `row` and a taget value `value` return the column `col_target` in 
 * which `val` is a naked candidate. Otherwise return -1. */
int col_cand_position(sudoku_grid_ptr s, int row, int value){
    int col_target = -1;
    for(int col=0; col<SUDOKU_S; col++){
        if(is_cand((*s)[row][col].candidate,value)){     // `value` is candidate
            if(col_target==-1) col_target=col;           // first time in the col
            else return -1;                              // not naked
        } 
    }
    return col_target;
}
/* Given a block `row0, col0` and a taget value `value` return the position 
 * `row_target, col_target` in  which `val` is a naked candidate. 
 * Otherwise return `-1 -1`. */
int block_cand_position(sudoku_grid_ptr s,int row0,  int col0, 
                        int value, int *target){
    for(int i=0; i<SUDOKU_L; i++){
        for(int j=0; j<SUDOKU_L; j++){
            // printf("%d, %d, %d\n", i,j,value);
            if(is_cand((*s)[row0+i][col0+j].candidate,value)){
                if(target[0]==-1 && target[1]==-1){
                    target[0] = row0+i;
                    target[1] = col0+j;
                }else return 0; 
            }
        }
    }
    return 1;
}
/* Transform binary candidate to decimal.*/
int cand_bin2dec(int bin){
    int dec = 0;
    while (bin >>= 1) {
        dec++;
    }
    return dec;
}

