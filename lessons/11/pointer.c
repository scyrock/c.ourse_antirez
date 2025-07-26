#include <stdio.h>

int main(void){
    /* str is a string, and stores 'aabb'.
     * In ASCII the following hexadecimal conversions hold:
     * a = 0x61
     * b = 0x62
     *
     * char variables have a dimension of 1 byte.
     * short variables have a dimension of 2 bytes.
     *
     * The pointer s is declared as a short type (despite being used for a char variable).*/
    char str[] = "aabb";
    short *s = (short*)str;
    
    /* Due to the fact that in C array variables can be accessed as strings, each
     * value of str can be printed. As expected the decimal representation of each
     * letter is printed*/
    printf("\'a\' > 0x61 > %d \n"
           "\'a\' > 0x61 > %d\n"
           "\'b\' > 0x62 > %d\n"
           "\'b\' > 0x62 > %d\n", str[0], str[1], str[2], str[3]);

    /* If the same process is performed with pointer s a different result is obtained.
     * Due to the fact that short variables have dimension 2 bytes, by s[0] the
     * next 2 bytes from the memory address are returned, and this corresponds to 'aa'.
     * At the same time s[1], keeping into account the dimension of short variables,
     * skips 2 bytes and returns 'bb'.
     * It is worth to notice that the bytes are handled using standard mathematical
     * positional system (
     *        |  Byte 1  |  Byte 2  |
     * ASCII  |   'a'    |   'a'    | > 'aa'
     * binary | 01100001 | 01100001 | > 0110000101100001 = 24929
     * hex    |   0x61   |   0x61   | > 0x6161           = 24929
     */
    printf("\'aa\' > 0x6161 > %d \n"
           "\'bb\' > 0x6262 > %d\n", s[0], s[1]);

    
    /* A similar exaple can be obtained using an array of intager values.*/
    char str2[] = {1, 1, 2,  2};
    short *s2 = (short*)str2;

    printf("0x0101 > %d \n"
           "0x0202 > %d\n", s2[0], s2[1]);
    return 0;
}
