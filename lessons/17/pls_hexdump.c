#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* pls1 implements a pls structure using *str. */
struct pls1 {
    long len;       // 8-bytes integer
    char *str;      // 8-bytes pointer
};

/* pls2 implements a pls structure using a fixed length string. */
 struct pls2 {
     long len;       // 8-bytes integer
     char str[20];     
 };

#define CHARS_PER_LINE 8 

/* Given a generic pointer `p` and the related content length `len` the content
 * is displayed in a hexdump-like style.*/
void hexdump(void *p, size_t len){
    /* Given the void pointer `p`, it is copied in a char pointer (1 byte) that is
     * the same dimension represented by two digits hexadecimal number.*/
    unsigned char *byte = p;
    size_t po = 0;

    for(size_t i=0; i<len; i++){
        /* Specifier `02X` prints value in hexadecimal format.*/
        printf("%02X ", byte[i]);
        
        /* If CHARS_PER_LINE values have been printed in the current line:
         * - Compute the number of padding elements and display them.
         * - A tab space is added.
         * - If the printed characters are human readable, the characters are displayed.
         * - A new line is added.*/
        if ( (i+1)%CHARS_PER_LINE==0 || i==(len-1) ){

            // Padding
            if ( i==(len-1) ){
                int pad = CHARS_PER_LINE - (len%CHARS_PER_LINE);
                pad = pad%CHARS_PER_LINE;
                for(int j=0; j<pad; j++) printf("~~ ");
            }            
            
            printf("\t");   // Add tab

            // Display human-readable characters
            for(size_t j=po; j<=i; j++){
                /* The following line implements ternary operator.
                 * Condition ? Action_true() : Action_false()
                 * The `Condition` is checked, if the condition is true
                 * `Action_true` is executed, otherwise `Action_false` is executed.
                 *
                 * This implementation is equivalent to:
                 * if(Condition){
                 *   Action_true();
                 * } else{
                 *   Action_false();
                 * }
                 * */
                int c = isprint(byte[j]) ? byte[j] : '.';
                printf("%c", c);
            }
            po = i+1;       // Update po
            printf("\n");   // New line
        } 
    }
}

int main(void){
    struct pls1 s1;

    /* `s1` is initialized. The memory for the string is allocated by malloc().
     * Despite the string length being 10, the allocated memory has dimension 11 to
     * store also the string terminator (eg '\0'). */
    s1.len = 10;
    s1.str = malloc(10+1);
    
    /* The function memcpy(*dst,*src,len) copies the content of length `len`
     * stored at the pointer `src` to `dst`. In this case, instead of the source
     * pointer a literal string is used. During the compilation process the
     * string is stored in the memory and the related pointer is provided to
     * memcpy().*/
    memcpy(s1.str, "1234567890",11);
    
    printf(">> pls1 test << \n \n");
    /* The following printf proves the fact that a literal string is converted
     * to a pointer by the compiler.*/
    printf("The test string pointer is: %p\n", "teststring");
    
    /* By hexdump it is possible to see the structure memory layout:
     * - The first 8-bytes contains the memory length.
     * - The second 8-bytes contains the string memory address.  */
    printf("The `s1.str` pointer is: %p\n", s1.str);
    hexdump(&s1, sizeof(s1));
    
    printf("\n \n >> pls2 test << \n \n");
    struct pls2 s2;

    /* All the `s2` structure is initialized to the value of 256 (FF). */
    memset(&s2,0xff,sizeof(s2));
    s2.len = 10;
    memcpy(s2.str, "1234567890",11);

    /* The pointer `s2.str` points to the end of the structure independently
     * from the length declared in the initialization. */
    printf("The `s2` pointer is: %p\n", &s2);
    printf("The `s2.str` pointer is: %p\n", s2.str);
    printf("The distance between `s2.str` and `s2` is: %d bytes\n", 
            (int)((long)s2.str-(long)&s2));
    hexdump(&s2, sizeof(s2));


    return 0;
}
