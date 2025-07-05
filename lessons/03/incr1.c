#include <stdio.h>

void incr(void){
    /*
     * Parameters: void - function takes no parameters
     * Return type: void - function doesn't return any value
    */
    int x = 1;          // Local variable initialized to 1
    x = x + 1;          // Increment x by 1
    printf("%d\n",x);
}

int main(void){
    incr();
    incr();
    incr();
    
    /*
     * Although the function incr() is called multiple times, the output value
     * is always the same (2).
     * This is due to the fact that x is a local variable of incr().
     * It is initialized at each instance, and it is destroyed at the end.
     */
    return 0;
}
