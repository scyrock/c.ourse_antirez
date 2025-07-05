#include <stdio.h>


int incr(int x){
    /*
     * Parameters:
     *   x - integer value to be incremented
     *
     * Returns: integer value incremented by 1
     */
    x = x + 1; 
    return x;
}

int main(void){
    int a = 10;

    // incr(a)
    /*
     * In this case the value of the variable a doesn't change. The value
     * returned by the function incr() is ignored.
     */

    a = incr(a);
    /*
     * In this case instead the value of a is updated, in particular:
     * - The current value of a (10) is passed to the function incr().
     * - The function incr() returns the incremented value (11).
     * - The returned value is assigned to the variable a.
     */
    printf("%d\n",a);

    /*
     * It is important to notice that in C the function receives as input a value
     * and not the reference to that value. This means that the variable
     * manipulated in the called function is a copy of the original one.
     *
     * In C it is possible to provide a reference to a variable using pointers.
     * This allows functions to modify the original variable directly.
     */
}
