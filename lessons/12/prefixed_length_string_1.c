#include <stdio.h>
/*The goal is to implement pre-fixed length string. This allows to handle
 * strings that contain null terms (e.g. \0) inside the string.
 * To this purpose each string is stored as follows:
 * - The first array byte is used to store the string length. (L)
 * - The remaining part of the array stores the string characters in ASCII
 *   format. (string content)
 * +-+--------------\\
 * |L| string content
 * +-+--------------\\
 * It is worth to notice that in this implementation the maximum allowed
 * string length is function of the maximum integer that can be represented
 * in the first byte.*/

/* The function receives the pointer to a string, the string text and its
 * length. The function stores the string following pre-fixed length string
 * implementation.*/
void ps_init(char *s, char *init, int len){
    /* The string length is an unsigned value, the pointer is properly
     * redefined by casting. This allows to move the variable range from
     * (-127,127) to (0,256).*/
    unsigned char *lenptr = (unsigned char*) s;
    *lenptr = len;                 // store the string length 
    for(int i=0; i<len; i++){
        s[i+1] = init[i];
    } 
}

/* Print the pre-fixed length string. */
void ps_print(char*s){
    unsigned char len = (unsigned char) *s;
    for(int i=0; i<len; i++){
        putchar(s[i+1]);
    }
    printf("\n");
}

int main(void){
    char buf[256];

    ps_init(buf,"Hell\000 World", 11);
    ps_print(buf);
    
    /* In this implementation the memory storage must be handled case-by-case.*/

    return 0;
}
