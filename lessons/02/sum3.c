#include <stdio.h>

int sum(int a, int b){
    /*
     * Parameters 'a' and 'b' are automatically initialized with the passed values.
     */

    int c;
    /*
     * 'c' is a local variable. it exists only within this function.
     * Is is created when function starts, and is destroyed when function ends
     */

    c = a+b;
    return c;
}

int main(void){
    printf("The sum is: %d\n",sum(8,7));
    
    /*
     * 1. sum(8, 7) is called first
     * 2. sum function executes and returns result
     * 3. printf receives the returned value and displays it
     *
     * To check the execution order, the following command can be used:
     * gcc sum3.c -S
     */
    return 0;
}
