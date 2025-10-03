#include <stdio.h>

#define SUDOKU_L 3
#define SUDOKU_S 9 
#define SUDOKU_DIM SUDOKU_S*SUDOKU_S

typedef struct{
    int value;          // Cell assigne value (0 if unknown)
    int candidate;      // Cell valid candidate stores in binary format 
                        // (1 if valid candidate)
}sudoku_cell;
typedef sudoku_cell sudoku_grid[SUDOKU_S][SUDOKU_S];
typedef sudoku_grid* sudoku_grid_ptr;

// >>>>> Candidate operation <<<<<
/* Set the candidate `val` in position [`row`][`col`] */ 
void set_candidate(sudoku_grid_ptr s, int value,int row, int col){
    (*s)[row][col].candidate |= (1<<value);
}

/* Unset the candidate `val` in position [`row`][`col`] */
void unset_candidate(sudoku_grid_ptr s, int row, int col, int value){
    (*s)[row][col].candidate &= ~(1<<value);
}

/* Return true if there is only one allowed candidate.*/
int only_one_candidate(int n){
    if ((n & (n - 1)) == 0) return 1; 
    return 0;
}

/* Transform binary candidate to decimal.*/
int candidate_bin2dec(int bin){
    int dec = 0;
    while (bin >>= 1) {
        dec++;
    }
    return dec;
}
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
    // https://sudoku.coach/en/play/400060001020038000310004050500000000038000709000000003000010875006903000700020000
    
    /*
    char sudoku_in[SUDOKU_DIM+1] = "400060001020038000310004050"
                                   "500000000038000709000000003"
                                   "000010875006903000700020000"; 
    */
    
    char sudoku_in[SUDOKU_DIM+1] = "200900007805147002730208100679301500001589206580670031150402098427000605960015400"; 
    // "000004009020000000004910760310570000000000080800040000030000907000300054078000020";
    //"200900007805147002730208100679301500001589206580670031150402098427000605960015400";
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
                        set_candidate(s,i,row,col);
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
                //while (n >>= 1) {
                //    val++;
                //}
                //print_binary((*s)[row][col].candidate);
                //printf("%d", (*s)[row][col].candidate);
                printf("Row %d - Col %d - Value %d\n", row+1, col+1, val);
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
        int row_candidate = 0;
        for(int row=0; row<SUDOKU_S; row++){
            continue;
        }
    }
}

int main(void){
    sudoku_grid sudoku;
    init_sudoku(&sudoku);
    display_sudoku(&sudoku);
    candidate(&sudoku);
    int done = 1;
    
    while(done) done = naked_candidate(&sudoku); 
   
    
    display_sudoku(&sudoku);
    return 0;
}
