#include <stdio.h>

/* typedef allows to define a new variable type.
 * In this case the new variable type name is `errorcode`, and the variable is
 * an integer value. */
typedef int errorcode;

/* This dummy function returns a variable of type `errorcode`.*/
errorcode foo(void){
    return -17;
}

/* typedef allows also to define a struct as a new variable type.
 * In this case the new variable name is `fract`.
 * The variable type `fract` is used to store fractions, given the numerator (`n`)
 * and the denominator (`d`).*/
typedef struct {
    int n;
    int d;
}fract;

/* typedef can also be used to define pointers to a type.
 * In this case, `fractptr` is a type variable to store a pointer to `fract`
 * variables.*/
typedef fract *fractptr;

int main(void){
    
    int a = foo();
    /* A variale of type `errorcode` is initialized and its value is set by foo().*/
    errorcode b = foo();
    printf("My error code is: %d\n", a);
    printf("My error code is: %d\n", b);
    
    /* The variable myfract, of type fract can be used as a structure to store
     * a fraction.
     * This allows to improve code readability. */
    fract myfract;
    myfract.n = 3;
    myfract.d = 7;
    printf("My fraction is: %d/%d\n", myfract.n, myfract.d);
    
    /* `myfract_trp` is a pointer to `myfract` */
    fractptr myfract_ptr = &myfract;
    printf("My fraction is stored at %p\n", myfract_ptr);
    return 0;
}
