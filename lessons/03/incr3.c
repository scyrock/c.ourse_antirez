#include <stdio.h>


void incr(void){
    /* 
     * - static allows to declare a persistent variable that can be accessed only by
     *   the function in which the variable is declared
     * - The variable retains its value between function calls.
     * - The value of x is increased at each call of the function incr()
     */
    static int x = 0;
    x = x + 1; 
    printf("%d\n",x);
}

int main(void){
    incr();
    incr();
    incr();

    // printf("%d\n",x)
    /* 
    * The compiler raises an error if the variable x is used outside the
     * function incr() because static variables can be accessed only
     * inside the function.
     */
    return 0;
}
