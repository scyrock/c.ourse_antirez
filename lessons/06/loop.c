#include <stdio.h>

int main(void){
    
    /*
     * again is a label. It identifies a specific point of the code.
     * Labels cannot start with a number.
     *
     * In this example:
     * - The i variable is initialized to 0
     * - The value is printed
     * - The i value is increased by 1
     * - If the i value is smaller than 10, the execution goes to the label again.
     */
    int i = 0;

again:
    printf("%d\n", i);
    i++;
    if (i<10) goto again;
    
    /*
     * The implementation obtained exploiting label and goto is very similar to the
     * one that can be obtained by a while loop.
     * while executes the block until the condition defined in round brackets is true.
     */
    i = 0;
    while(i<10){
        printf("%d\n",i);
        i++;
    }

    /*
     * ! is the not boolean operator in C.
     * If condition A is true !A is false, and vice versa.
     *
     * The while loop can be implemented by goto as follows:
     * The condition (!(i>10)) is checked:
     * - If the condition is true:
     *   + i is printed
     *   + i is increased by one
     *   + code execution is moved to the loop label
     * - If the condition is false:
     *   + code execution is moved to the next label
     */

    i = 0;
    loop:
    if(!(i<10)) goto next;
        printf("%d\n",i);
        i++;
        goto loop;
    next:
    
    /*
     * To use the same condition used in the while a possible
     * implementation is the following:
     */
    
    i = 0;

    loop1:                  // main loop
    if(i<10) goto incr;     // check the termination condition
    goto terminate;         // skip to loop end
    incr:                   // print and increment i
        printf("%d\n",i);
        i++;    
    goto loop1;             // repeat the main loop
    terminate:
    
    return 0;
}
