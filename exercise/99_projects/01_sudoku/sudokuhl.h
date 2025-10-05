// Collect all the helping functions for sudoku resolution.

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


