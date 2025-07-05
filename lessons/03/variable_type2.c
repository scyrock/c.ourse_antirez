#include <stdio.h>

int main(void){

    /*
     * int variables allow to store positive and negative integer values.
     * Typically 32-bit signed integers.
     */
    int a = 10; 

    /*
     * unsigned int variables allow to store only positive integer values.
     * Typically 32-bit unsigned integers.
     */
    unsigned int b = 20;

    /*
     * float variables allow to store decimal numbers within a certain precision.
     * float variables are stored using fp32 representation.
     * This format allows to properly store both very small and very large values.
     */
    float y = 1.234;

    /*
     * char variables allow to store small integer numbers,
     * usually between -128 and 127 (1 byte - 8 bits).
     */
    char c = 8;

    /*
     * short variables allow to store integer numbers,
     * usually between -32,768 and 32,767 (2 bytes - 16 bits).
     */
    short d = -182;
    
    /*
     * To simplify the implementation of certain functionalities, a promotion
     * system is implemented. In this case, before printing the value,
     * the short variable d is promoted to an integer.
     * Float numbers are promoted to double before printing.
     */
    printf("%d\n", d);

    /*
     * In this case the variables are wrongly assigned.
     * %d expects an integer as first variable, but a float value is provided.
     * Vice versa for %f (expects float but gets integer).
     * During compilation the compiler could raise some warnings, but the code
     * is compiled anyway. This is dangerous because it can generate
     * unexpected behavior and garbage output.
     */
    printf("%d %f\n", y,a);

    return 0;
}
