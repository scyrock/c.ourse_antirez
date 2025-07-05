#include <stdio.h>

int main(void){
    int a = 10;
    float y = 1.234;

    /*
     * printf allows to perform different formatting manipulations:
     * %.2f specifies that only two decimal digits are printed after the decimal point.
     */
    printf("Print only two decimal digits:%.2f\n",y);
    
    /*
     * %x prints the integer number in hexadecimal format (lowercase).
     * %X would print in uppercase hexadecimal format.
     */
    printf("Print %d in hexadecimal format:   %x\n",a,a);
    
    /*
     * %d - signed decimal integer
     * %f - floating-point number (promoted to double see variable_type2.c)
     */
    printf("%d %f\n", a,y);

    return 0;
}
