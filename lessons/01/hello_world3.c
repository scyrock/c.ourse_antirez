#include <stdio.h>

int main(void){
    /*
     * With the #include directive the compiler
     * replaces this line with the contents of the specified file
     * before compilation begins.
     *
     * The compiler will insert the contents of file.c at this location,
     * making it as if the printf statement was written directly here.
     */
    #include "file.c"

    return 0;
}
