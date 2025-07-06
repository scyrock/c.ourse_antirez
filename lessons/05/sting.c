#include <stdio.h>

int main(void){
    char c = 10;
    /*
     * The function printf allows to print variables using specifiers.
     * In this specific case the char variable c is
     * promoted to int type and then is printed.
     */
    printf("The number is: %d\n",c);

    /*
     * In this case the char variable d receives as initialization value 'A'.
     * In C language the single character contained between single quotes (')
     * is expanded to the corresponding ASCII standard value.
     * It is possible to access it by terminal command: ascii.
     * If special characters are used, the value is transformed to a byte value
     * out of ASCII standard.
     */
    char d ='A';
    printf("The ASCII value corresponding to A is: %d\n", d);

    /*
     * In vim environment by command Ctrl+v followed by Ctrl+{target key} the
     * following character is interpreted as verbatim: the raw keyboard
     * signal is written.
     * As an example in this case the value is mapped to 1.
     */
    char e ='';
    printf("The ASCII value corresponding to  is: %d\n", e);

    /*
     * "Literal types" define the types of variables that natively are supported
     * by a programming language. In C there are few literal types.
     * char is one of them.
     */

    /*
     * Another C literal type is the string.
     * The format specifier %s can be used to print the string content.
     * Now the output string may contain also other characters or variables.
     */
    printf("[-%s-]\n","Hello world");

    /*
     * printf automatically converts integer values to the corresponding char.
     * In this case as an example given the correspondence between A and 65
     * (known from previous example), the subsequent letters can be printed.
     */
    printf("[-%c,%c,%c-]\n", 65,66,67);

    /*
     * Thanks to the fact that a letter within single quotes is automatically
     * converted to the corresponding ASCII value, using the same output string
     * the implementation can be combined.
     */
    printf("[-%c,%c,%c-]\n", 65,'x',67);
    printf("[-%c,%d,%c-]\n", 65,'x',67);

    return 0;
}
