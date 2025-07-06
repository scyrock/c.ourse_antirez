#include <stdio.h>

/*
 * stdint.h library allows to overcome the limitations presented below.
 * uint64_t - defines an unsigned integer 64 bits variable
 * int64_t - defines an integer 64 bits variable
 * size_t - defines the maximum size that can be defined on that processor
 */
// #include <stdint.h>

int main(void){
    /*
     * All the information provided below refers to the most common
     * implementation in modern devices.
     * This information is not ensured by the C standard.
     */
    
    /*
     * char - 8 bits (1 byte) integer.
     * char is pivotal in C because it allows to represent, store and
     * manipulate strings (text).
     * Range: typically -128 to 127 (signed) or 0 to 255 (unsigned)
     */
    char c = 10;
    printf("char type has a dimetion of %lu bytes\n", sizeof(c));
    
    /*
     * short - 16 bits (2 bytes) integer.
     * If it is needed to store small values, the use of short variables allows to
     * optimize the space (4 short variables fit in 1 long variable).
     */
    short s = 1000;
    printf("short type has a dimetion of %lu bytes\n", sizeof(s));
    
    /*
     * int - 32bits (4 bytes) integer.
     */
    int i = 4321;
    printf("int type has a dimetion of %lu bytes \n", sizeof(i));
    
    /*
     * long - 64 bits (8 bytes) integer on 64-bit systems.
     * Usually long type has the same dimension as the processor architecture.
     * long format is useful to avoid overflow in different operating conditions
     * such as mathematical operations between int variables or for long-time processes.
     */
    long l = 49321;
    printf("long type has a dimetion of %lu bytes \n", sizeof(l));
    
    /*
     * The absence of a unified convention could generate unexpected behavior.
     * This is common when old C programs are compiled on new machines, because
     * sometimes they are based on the assumption that an int variable
     * can store a memory address.
     * (int - 32 bits vs memory address in modern processor - 64 bits)
     */

    /*
     * In "modern" implementations of C it is possible to use other variable
     * types, such as:
     * - intptr_t - ensures that a memory address can be stored.
     *   Despite using unsigned variables to store memory addresses (that are unsigned
     *   by design), this could be useful to perform mathematical basic operations.
     * - uintptr_t - unsigned memory address.
     */
    return 0; 
}
