#include <stdio.h>

int main(void){
    /*
     * Curly brackets define a block.
     * Blocks can be defined independently from other instructions.
     */
    {
        printf("Hello world\n");
    }

    /*
     * The variable i is defined inside the block, for this reason can be only
     * accessed inside the block.
     * Printing the variable outside the block raises an error.
     */
    {
        int i = 5;
        printf("i is equal to %d\n", i);
    }
    // printf("i is equal to %d\n", i);
   
    /*
     * In this case, despite both variables have the same name, they refer
     * to two different values. Inside the block the value is 5, in the rest
     * of the main function the value is 8.
     */
    int i = 8;
    {
         int i = 5;
         printf("i is equal to %d\n", i);
     }
    printf("i is equal to %d\n", i);
    
    /*
     * & before the variable name allows to access the memory address in
     * which the variable is stored.
     * %p specifier allows to print pointers.
     * %zu specifier is used for size_t variables (is similar to %lu).
     *
     * The output emphasizes that the two variables address to two different values.
     * Can be noted that the distance between the two memory addresses corresponds
     * to the length of the variable (4 bytes).
     *
     * Despite the compiler could implement other strategies (such as keeping
     * allocated a block variable also when the block execution is terminated),
     * it is important to take into account that the variables defined inside a
     * block are initialized at the beginning of the block and deleted at the end.
     */

    int j = 8;
    {
        int j = 5;
        printf("j-block variable, with a dimention of "
                "(%zu bytes) is stored at: %p\n",sizeof(i), &j);
    }
    printf("j-block variable, with a dimention of "
           "(%zu bytes) is stored at: %p\n",sizeof(i), &j);

    return 0;
}
