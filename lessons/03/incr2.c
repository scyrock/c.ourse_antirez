#include <stdio.h>

int x = 0;          // x is a global variable 

void incr(void){
    /* 
     * The variable is created when the program starts, ad is value is persistent.
     * The global variable x is accessible from any function.
     * Its value persists throughout the program's execution.
     */
    x = x + 1; 
    printf("%d\n",x);
}

int main(void){
    /*
     * Each call to incr() modifies the same global variable.
     */
    incr();
    incr();
    incr();
    return 0;
}
