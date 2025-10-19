#include <stdio.h>

void hello(void){
    printf("Hello!\n");
}

void baubau(void){
    printf("BauBau...\n");
}

/* The function calls the function pointed to by `fcn`, `n` times. */
void call_n_times(int n, void (*fcn)(void)){
    /* By using the post-decrement operator (`n--`), the value of `n` is used in the
     * condition first, and then decremented. In contrast, the pre-decrement operator
     * (`--n`) decrements the value first, and then performs the evaluation.*/
    while(n--){
        printf("%d: ", n+1);
        fcn();
    }
}
int main(void){
    /* Functions hello() and baubau() share the same prototype (e.g., they both
     * take no arguments and return `void`). Hence, the function pointer `x` can
     * store the address of either function. */
    void (*x)(void);

    x = hello;  // set x pointer to function hello()
    x();
    x = baubau; // set x pointer to function baubau()
    x();

    /* Functions hello() and baubau() are passed as arguments to the function
     * call_n_times(). */
    call_n_times(4, hello);
    call_n_times(5,baubau);
    return  0;
}
