#include <stdio.h>

/* The operation of accessing to the variable by the pointer, using *p or p[0]
 * is called dereferencing. Dereferencing means accessing to a value by its memory
 * address. This process can be performed both in read and write. */
void incr(int *p){
    printf("incr - The value of x is:%d\n",*p);
    p[0] = p[0]+1;
}
int main(void){
    int x = 8;
    printf("main - The initial value of x is: %d\n", x);
    incr(&x);

    printf("%d\n", x);
    printf("main - The incremented value of x is: %d\n", x); 
    return 0;
}
