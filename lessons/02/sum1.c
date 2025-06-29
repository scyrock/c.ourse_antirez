#include <stdio.h>

int sum(int a, int b){
    /* The sum function:
     * revives as input two intager values (a and b)
     * return an intager value that rapresent the sum of the two values */
    return a+b;
}

/* In c the main function has a special role. 
 * It is runned, despite it is not invoked in any other part of the code.
 * in absence of the main function the c code cannot be compiled */
int main(void){
    printf("The sum is: %d\n",sum(8,7));
    /* printf is the abbreviation of Print Formatted.
     * The first argument of the function ("The sum is: %d\n") provide the output format.
     *
     * The spiecial character %d inform the printf function that an intager value will be provided. */

    // printf("The sum is: %d %d\n",sum(8,7));
    /* If there is not coherence between the expected arguments and the actual one:
     * 1. The compiler should rise error
     * 2. The visualize velue will be random, and not univocally defined. */
    return 0;
}
