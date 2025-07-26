#include <stdio.h>

int main(void){
    char str[] = "Hello0World";
    char *s = str;
    
    /* The while loop iterates until the value pointed by s is not null.
     * It is worth to notice:
     *  - In C the following conditions hold:
     *      True condition = 1
     *      False condition = 0
     *  - The value 0 is used as terminator for strings.
     *
     *  Despite the string contains 0, all the string is printed.
     *  This happens because the character 0 is stored in ASCII representation. */
    while(*s){
        putchar(*s);
        s++;
    }
    printf("\n");

    printf("In string: %s\n"
           "the character %c is rapresented by ASCCI value %d\n", 
           str, str[5],str[5]);
    
    /* By using the ASCII representation of 0, it is possible to print only 'Hello' */
    char *s2 = str;
    while(*s2 != 48){
        putchar(*s2);
        s2++;
    }
    printf("\n");
    
    /* \000 is the octal representation of 0. In this case the stored byte is 0,
     * and the while loop properly terminates. */
    char str3[] = "Hello\000World";
    char *s3 = str3;
    while(*s3){
        putchar(*s3);
        s3++;
    }
    printf("\n");
    
   /* To safely handle string print the following approach can be used:
     * - The string has as initial byte the length expressed in octal, in this case
     *   the length is 11, that corresponds to \013.
     * - An integer variable (e.g. len) is used to store the string length. Moreover
     *   the pointer s4 is increased by one.
     * - A for loop is used to safely print the string.
     *
     * It is worth to notice that \000 is not printed, because it does not correspond
     * to any character in ASCII notation.
     *
     * This solution is called "prefix length string". */
    char str4[] = "\013Hello\000World";
    char *s4 = str4;
    int len = *s4++;
    
    for(int i=0; i<len; i++){
        putchar(s4[i]);
    }
    printf("\n");

    return 0;

}
