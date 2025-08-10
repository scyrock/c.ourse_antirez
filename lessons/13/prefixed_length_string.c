#include <stdio.h>
#include <stdlib.h>     // to use malloc()
#include <stdint.h>     // to use uint32_t

/* The following code improves the pre-fixed length string (pls) implementation
 * proposed in /12/prefixed_length_string_2.c.
 * In particular:
 * - The maximum string length is increased to 2^32-1 (4-bytes to store the
 *   string length).
 * - Improves pls interoperability with standard C string, by pointing directly
 *   to the string text, instead of the overhead.
 * - Evaluates the pls length in computationally efficient manner.
 * - Tracks the number of string references (reference counting). The pls memory
 *   is cleared when the reference count is zero. (TODO)
 *
 * +----+-----\\---------+--+
 * |LLLL| string content |\0|
 * +----+-----\\---------+--+
 *       s*
 *       ^
 */

/* Create the pls */
char *ps_create(char *init, int len){
    /* The allocated memory is increased to fulfill the new pls implementation.*/
    char *s = malloc(4+len+1); 
    /* To ensure that the length dimension is 32 bit (4-bytes) on all hardware
     * the variable type uint32_t is used.*/
    uint32_t *lenptr = (uint32_t*)s;
    *lenptr = len;
    
    s+=4;       // skip the pls length
    for(int i=0; i<len; i++){
        s[i] = init[i];
    }
    
    return s; // the function return the pointer to the first character 
}

/* Print the pls*/
void ps_print(char*s){
    uint32_t *len = (uint32_t*)(s-4);
    for(int i=0; i<*len; i++){
        putchar(s[i]);
    }
    printf("\n");
}

/* Free the pls memory allocation */
void ps_free(char*s){
    free(s-4);
}

/* Return the pls length */
uint32_t ps_len(char *s){
    /* Compared to standard functions to evaluate the string length, in this case,
     * thanks to the pls structure, it is not necessary to analyze all the string
     * structure.*/
    uint32_t *lenptr = (uint32_t*)(s-4);
    return *lenptr;
}

char *global_string;

int main(void){
    char *mystr = ps_create("Hello WorldHello WorldHello World", 33);
    global_string = mystr;  // global_string points to the same value of mystr
    ps_print(mystr);
    printf("The string length is %d\n", (int)ps_len(mystr));
    printf("%s\n", mystr);
     
    ps_free(mystr);
    /* If the same memory is cleared multiple times memory corruption may occur*/
    //ps_free(mystr);

    /* Despite the mystr memory is cleared global_string still points to mystr.
     * global_string is pointing to a memory address that is not well defined.*/
    printf("%s\n", global_string);
    

    return 0;
}
