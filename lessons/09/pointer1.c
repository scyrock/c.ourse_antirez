#include <stdio.h>

int main(void){
    int x = 8;

    /*
     * y is a pointer to an integer variable.
     * * before the variable name identifies the pointers.
     * The name of the variable is y, * is only used to declare it as pointer.
     *
     * It is also possible to declare a pointer as follows:
     * int* y, z;
     * This may cause confusion. In this case as an example only y is a pointer,
     * z instead is an int variable.
     *
     * In this case the pointer is initialized to 0. 0 identifies a special memory
     * address called null address (nil). The same result can be obtained also by
     * using the special keyword NULL.
     *
     * Despite memory addresses are independent from the data type stored inside it
     * is necessary to declare the pointer data type. This is pivotal because if
     * the variable is modified using the pointer the compiler must know which type
     * is the manipulated variable.
     */
    int *y=0;
    // int *y=NULL;

    printf("The initial value of x is: %d\n", x);

    /*
     * To print the pointer value specifier %p is used.
     */
    printf("%p\n", y);
    
    /*
     * By the following operation the x memory address is assigned to the
     * pointer y.
     * & operator before a variable name allows to access the variable memory
     * address.
     */
    y = &x;
    printf("x variable is store at the adress: %p\n", y);
   
    /*
     * By this expression, the variable with memory address equal to y is set to 10.
     * This proves the importance of initializing the pointer variable type.
     *
     * The same operation can be performed also by y[0] = 10.
     * This is possible because y is a memory address that at position 0 contains
     * the variable x.
     * In case of arrays the same approach can be used to access the next values.
     */
    *y = 10;
    // y[0] = 10;
    printf("The value of x is: %d\n", x);
    
    return 0;
}
