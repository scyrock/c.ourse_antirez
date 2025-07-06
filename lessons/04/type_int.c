#include <stdio.h>
#include <limits.h>

int main(void){
    /*
     * Differently from other programming languages, in C the characteristics of
     * the dimension of the different variables are not defined by the standard.
     * This is due mainly to historical reasons and the necessity/scope to
     * create a cross-platform code language that can be implemented on a
     * variety of hardware devices.
     */

    int x =5;

    /*
     * sizeof() allows to know the dimension in bytes of the variable.
     * sizeof returns a value of type unsigned integer type
     */
    printf("On this machine the int variale has a size of %d bytes\n", sizeof(x));

    /*
     * During the compilation a warning is raised.
     * This is because printf expects an integer value (%d) but an unsigned long (%lu) is passed.
     * The correct format specifier for sizeof is %lu.
     */
    printf("On this machine the int variale has a size of %lu bytes\n", sizeof(x));
    
    /*
     * USUALLY int type has a dimension of 4 bytes, that implies 2^32 possible values.
     * int can represent values between -2^31 and 2^31-1 (signed).
     * unsigned int can represent values between 0 and 2^32-1 (unsigned).
     *
     * The actual ranges depend on the implementation and architecture.
     */
    
    /*
     * Thanks to the limits.h library, the minimum and maximum values can be
     * easily accessed using predefined constants.
     */
    printf("The minimum value for int variable is: %d\n"
           "The maximum value for int variable is: %d\n",
            INT_MIN, INT_MAX);

    return 0; 
}
