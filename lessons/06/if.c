#include <stdio.h>

int main(void){
    /*
     * In C if statement is defined by:
     * - a condition, defined inside round brackets
     * - a block, defined inside curly brackets
     * If the condition is true, the subsequent block is executed.
     *
     * When the if condition is false, if else is present, the else block is executed.
     */

    int i = 5;
    if (i>3){
        printf("%d is greather than 3\n", i);

    } else {
        printf("%d is smaller or equal 3\n", i);
    }    
    
    /*
     * If only a statement is performed, it is not necessary to define a block
     * by curly brackets.
     */
    if (i>3) printf("%d is greather than 3\n", i);
    
    /*
     * This implementation can be extended also to else.
     * Moreover C is not sensitive to space or indentation, only the semicolon
     * defines the end of a line.
     */
    if (i>3)
        printf("%d is greather than 3\n", i);
    else 
        printf("%d is smaller or equal 3\n", i);
    
    return 0;
}
