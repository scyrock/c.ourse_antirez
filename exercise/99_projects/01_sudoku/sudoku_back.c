#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SUDOKU_L 3
#define SUDOKU_S 9 
#define SUDOKU_DIM SUDOKU_S*SUDOKU_S
#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_RESET    "\x1b[0m"

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
    //char sudoku_in[SUDOKU_DIM+1] = "400060001020038000310004050500000000038000709000000003000010875006903000700020000";   
    char sudoku_in[SUDOKU_DIM+1] = "200900007805147002730208100679301500001589206580670031150402098427000605960015400"; 
    // char sudoku_in[SUDOKU_DIM+1] = "000031000040702009000090002000000600090008010120070090700000900006400005250000000";
    
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

/* Display the sudoku scheme */
void display_sudoku_v2(sudoku_grid_ptr s, sudoku_grid_ptr root){
    int row = 0;
    int col = 0;
    separation_line();
    for(row=0; row<SUDOKU_S; row++){
        printf("|");
        for(col=0; col<SUDOKU_S; col++){
            if((*s)[row][col].value != 0){
                if((*root)[row][col].value != 0){
                    printf("%s%d%s", ANSI_COLOR_RED,(*s)[row][col].value, ANSI_COLOR_RESET);
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
    int row_g = prev_bt->row_g;
    int col_g = prev_bt->col_g;
    int val_g = prev_bt->val_g;
    
    memcpy(new_bt, prev_bt, sizeof(struct bt_node));
    
    new_bt->grid[row_g][col_g].value = val_g;
    printf("\n >>> APPEND: node in position [%d,%d] has value: %d\n",
           row_g, col_g, new_bt->grid[row_g][col_g].value);
    new_bt->grid[row_g][col_g].candidate = 0;
    
    release(&(new_bt->grid), row_g, col_g, val_g);
    // Initialize node guesses
    new_bt->row_g = 0;
    new_bt->col_g = 0;
    new_bt->val_g = 0;
    new_bt->prev_node = prev_bt;
    
    return new_bt;
}
/* A new memory adress must be returned with the new location.*/
struct bt_node *pop_node_validity(struct bt_node *in_node, struct bt_node *root){
    // printf("IN PTR: %p\n", in_node);
    struct bt_node *out_node = in_node;
    for(int row=0; row<SUDOKU_S; row++){
        for(int col=0; col<SUDOKU_S; col++){
            if(in_node->grid[row][col].value==0 && in_node->grid[row][col].candidate==0){
                out_node = in_node->prev_node;
                printf("Free on %p\n", in_node);
                free(in_node);
                printf("\n >>>POP   : node in position [%d,%d] has value: %d\n", 
                        out_node->row_g, out_node->col_g, out_node->grid[out_node->row_g][out_node->col_g].value);
                int row_g = out_node->row_g;
                int col_g = out_node->col_g;
                int val_g = out_node->val_g;
                unset_cand(&(out_node->grid), row_g, col_g, val_g);
                out_node->val_g++;
                return out_node;
            }
        }
    }
    // printf("OUT PTR: %p\n", out_node);
    return out_node ;
}


void bt_solver(struct bt_node *root, struct bt_node *node){
    int row_g = node->row_g;
    int col_g = node->col_g;
    int val_g = node->val_g;
   
    for(int row=row_g; row<SUDOKU_S; row++){
        for(int col=col_g; col<SUDOKU_S; col++){
            for(int val=val_g; val<=SUDOKU_S; val++){
                if(node->grid[row][col].value==0 && valid_cand(&(node->grid),row,col,val)){
                    // print_binary(node->grid[row][col].candidate); 
                    node->col_g = col;
                    node->row_g = row;
                    node->val_g = val;
                    struct bt_node *new_node = init_bt_node(node);
                    node = new_node;
                    // printf("Previous node ptr: %p\nActual node ptr: %p\n", node->prev_node, node); 
                    printf("\x1b[H\x1b[2J\x1b[3J");
                    printf("\n\nPTR: %p, row_g %d, col_g %d, val_g %d\n",
                                    node, node->row_g, node->col_g, node->val_g);
                    display_sudoku_v2(&(node->grid),&(root->grid)); 
                    usleep(5000);
                    int flag = 1;
                    while(flag){
                        new_node = pop_node_validity(node, root);
                        if(node == new_node){
                            flag = 0;
                        }else{
                            node = new_node;
                            printf("\x1b[H\x1b[2J\x1b[3J");
                            printf("\n\nPTR: %p, row_g %d, col_g %d, val_g %d\n",
                                    node, node->row_g, node->col_g, node->val_g);
                            display_sudoku_v2(&(node->grid),&(root->grid)); 
                        }
                        node = new_node;
                    }
                if(node->val_g>9){
                    // printf(">>>> Over 9 <<<<");
                    new_node = node->prev_node;
                    free(node);
                    node = new_node;
                    node->val_g++;
                    bt_solver(root, node);
                }
                bt_solver(root, node);
   
                }
                struct bt_node *new_node;
                if(node->val_g>=9){
                    // printf(">>>> Over 9 <<<<");
                    new_node = node->prev_node;
                    free(node);
                    node = new_node;
                    node->val_g++;
                    bt_solver(root, node);
                }
                
            }
            val_g = 1;
        } col_g = 0;
    } 
} 

int main(void){ sudoku_grid sudoku; init_sudoku(&sudoku); candidate(&sudoku);

    // Initialize root node.
    struct bt_node root_node;
    root_node.prev_node = 0;
    root_node.row_g = 0;          
    root_node.col_g = 0;
    root_node.val_g = 0; 

    memcpy(&root_node.grid,&sudoku,sizeof(sudoku));
    bt_solver(&root_node,&root_node);
    display_sudoku_v2(&root_node.grid,&root_node.grid);
    return 0;
}
