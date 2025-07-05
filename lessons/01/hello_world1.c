/*
 * The directive `#include <stdio.h>` ensures that the standard
 * input/output library is loaded before compilation.
 * C code has a minimal set of core keywords (e.g., `int`, `return`);
 * all other functionalities must be included through appropriate libraries.
 * Typically, header files (`.h`) are used to store code that provides
 * auxiliary functions and utilities, which can be shared across multiple C files.
 */
#include <stdio.h>

int main(void){
    /*
     * The main function is the entry point of every C program.
     * Return type: int - returns an integer status code
     * Parameters: void - takes no parameters
     */

    printf("Hello world\n");

    /*
     * To execute the code it is necessary to:
     * 1. Compile: gcc hello_world1.c (generates a.out binary)
     * 2. Execute: ./a.out
     */

    /*
     * To get more information about the binary file it is possible to
     * view binary contents: hexdump -C a.out | less
     *
     * It is also possible Generate assembly instruction:
     * gcc -S hello_world.c (creates hello_world.s)
     *
     * The compiler can optimize the  assembly code generation:
     * - Use -On flag where n is 0-3: gcc -O2 -S hello_world.c
     * - Higher optimization may replace printf with puts for better performance
     * - puts automatically appends newline, so compiler may remove \n from string
     */

    return 1;
    /*
     * Return 1 indicates program execution with an error status
     * Check return value with: ./a.out; echo $?
     */
}
