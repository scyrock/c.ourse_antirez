#include <stdio.h>

int sum(int a, int b){
    /*
     * Parameters:
     *   a - first integer operand
     *   b - second integer operand
     *
     * Returns: integer sum of a and b
     */
    return a+b;
}

/* In c the main function has a special role. 
 * It is runned, despite it is not invoked in any other part of the code.
 * in absence of the main function the c code cannot be compiled */
int main(void){
    /*
     * The main function has special significance in C:
     * - The program starts execution from main()
     * - Without main(), the program cannot be compiled into an executable
     */

    printf("The sum is: %d\n",sum(8,7));
    /*
     * printf stands for "Print Formatted"
     * %d is the format specifiers for integer
     * The number of format specifiers must match the number of arguments
     * that follow the format string, otherwise undefined behavior occurs.
     */

    // printf("The sum is: %d %d\n",sum(8,7));
    /*
     * Two format specifiers (%d %d) but only one argument (sum(8,7))
     * If there is not coherence between the expected arguments and the actual one:
     * 1. The compiler should rise error
     * 2. Runtime behavior is undefined - may print garbage values
     */
    return 0;
}
