#include <stdio.h>

int main(void){
    /* To declare a pointer to a function is needed to:
     * - Write the function prototype.
     * - Put the pointer name between brackets.
     * - Insert an asterisk before the pointer name. */
    int (*myfcn)(void);
    myfcn = main;

    /* Like many other elements in C, functions can also be handled by a pointer. */
    printf("The main() function pointer is: %p\n", main);
    /* The pointer `myfcn` has the same address value of function main. */
    printf("The myfcn pointer is: %p\n", myfcn);

    /* The pointer can be used also to call the function. In this case as an
     * example call `myfcn()` and `main()` provide the same result.*/
    myfcn();
    // main();
    return  0;
}
