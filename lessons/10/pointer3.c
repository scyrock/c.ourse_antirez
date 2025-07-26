#include <stdio.h>

/* All the discussed pointer characteristics can be exploited also in functions.
 * In this case as an example the function printstr receives as argument the pointer
 * to the first value of mystr to print. The process continues until when the
 * termination value '.' is found.*/
void printstr(char *p){
    while (*p != '.'){
        putchar(p[0]);
        p++;
    }
    printf("\n");
}
int main(void){
    char mystr[] = "AABBCCDDEE.FF";
    char *p = mystr;
    printstr(p);
    printstr(p+3);    

    return 0;
}
