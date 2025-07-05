#include <stdio.h>

int main(void){
    unsigned char c = 255;
    c++; //This is equivalent to c = c+1.
    /*
     * unsigned char variables usually can represent values between 0 and 255.
     * In this case, after the increment, the c value is out of range.
     * 256 exceeds the maximum value for unsigned char.
     */
    
    /*
     * If the value is printed, the output is 0.
     * This behavior is called wrapping and is implemented in C language
     * to handle overflow ONLY for unsigned integers.
     * For signed integers, overflow behavior is undefined.
     */
    printf("%d\n", c);
    
    /*
     * In this second case instead, the code is executed as expected. This
     * is because when a mathematical operation is performed,
     * the promotion system is implemented.
     * The char value is promoted to int before the addition,
     * so no overflow occurs in the computation.
     */

    char d = 127;
    int i = d+1;

    printf("%d\n",i);

    return 0;
}
