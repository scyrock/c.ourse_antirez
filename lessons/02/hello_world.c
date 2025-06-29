#include <stdio.h>

int main(void){
    /*
     * The main function is the entry point of every C program.
     * Return type: int - returns an integer status code
     * Parameters: void - takes no parameters (modern C allows empty parentheses)
     * Convention: return 0 indicates successful program execution
     * non-zero values indicate various error conditions
     */

    printf("Hello World\n");
    return 0;

    /*
     * To view the return value after execution, use: ./a.out; echo $?
     * This convention can be useful to chaining the execution of different commands (e.g. `./a.out && ls`). */
}

/*
 * Add the flag -W -Wall to gcc command allow to receive warnings during
 * the code compilation.
 */
