#include <stdio.h>

/*
 * In this case the variable is incremented by using the pointer to the variable.
 * The function receives as input the variable memory address.
 * Accesses to the x actual value by *p, increases it by 1, and writes the updated value
 * at the same memory address.
 */
void incr(int *p){
    *p = *p+1;
    // p[0] = p[0]+1;
}

int main(void){
    int x = 8;
    int *y = NULL;
    
    printf("The initial value of x is: %d\n", x);
    
    /*
     * The auxiliary variable y can be avoided, by providing as incr argument
     * the x pointer.
     */
    y = &x;
    incr(y);
    incr(&x);
    printf("The incremented value of x is: %d\n", x);
    return 0;
}
