#include <stdio.h>

int main(void){
    /* In c it is always necessary to define the variable type.
     * In this case three different intager varibles are declered.
     * a,b are initialized to a predefined value
     * c is initialized as a funtion of an expression. */

    int a = 3;
    int b = 8;
    int c = a+b;
    
    // int a,b,c;
    // a = 3
    // b = 8
    // c = a+b
    
    /* A variable should be created without initialized is value. */
    
    printf("The sum is: %d\n", c);
    return 0;

}
