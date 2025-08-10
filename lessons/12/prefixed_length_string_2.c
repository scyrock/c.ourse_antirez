#include <stdio.h>
#include <stdlib.h>     // to use malloc()

/* The function returns the pointer of the pre-fixed length string.*/
char *ps_create(char *init, int len){
    /* By malloc() a memory block of dimension len+1 is allocated.
     * The pointer s stores the allocated memory address.*/
    char *s = malloc(len+1);
    unsigned char *lenptr = (unsigned char*)s;
    *lenptr = len;

    for(int i=0; i<len; i++){
        s[i+1] = init[i];
    }
    
    /* It is worth to notice that by malloc() and pointer s the memory
     * can be accessed also outside the function ps_create.*/
    return s;
}

/* This function enhances `ps_create` by adding the terminator to the string.
 * +-+----\\----------+--+
 * |L| string content |\0|
 * +-+----\\----------+--+
 */
char *ps_create_terminate(char *init, int len){
    char *s = malloc(len+2);
    unsigned char *lenptr = (unsigned char*)s;
    *lenptr = len;
     
    for(int i=0; i<len; i++){
        s[i+1] = init[i];
    }
    s[len+1] = 0;
    
    return s;
}

/* Print the pre-fixed length string. */
void ps_print(char*s){
    unsigned char len = (unsigned char) *s;
    for(int i=0; i<len; i++){
        putchar(s[i+1]);
    }
    printf("\n");
}

/* Given a pre-fixed length string, return a string in C format.*/
char *ps_get_c(char *s){
    return s+1; // skip the stirng length
}
int main(void){
    char *mystr = ps_create("Hell\000 World", 11);

    ps_print(mystr);  
    /* If the string is printed by printf, there are at least three issues:
     * 1. The first byte (string length), will be interpreted as an ASCII value
     *    and printed (e.g. 11 is converted to `vt`).
     * 2. The presence of null value inside the string stops the print.
     * 3. printf() will print until the next terminator byte, which is not properly
     *    defined. */
    printf("%s\n", mystr);
    
    
    char *mystr2 = ps_create("Hello World Hello World Hello World", 35);
    char *mystr3 = ps_create_terminate("Hello World Hello World Hello World", 35);

    printf("%s\n", mystr2);

    /* By combining `ps_create_terminate` and `ps_get_c` the first byte is skipped,
     * and the string is properly terminated. This allows a compatibility between
     * pre-fixed length string and C string.*/
    printf("%s\n", ps_get_c(mystr3));
    
    /* free() allows to clean the memory previously allocated by malloc(). */
    free(mystr);
    free(mystr2);
    free(mystr3);

    return 0;
}
