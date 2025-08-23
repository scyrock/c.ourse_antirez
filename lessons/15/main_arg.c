#include <stdio.h>
    
/* main function could have arguments.
 * By default main function has two arguments:
 * - `argc`: the number of arguments.
 * - `**argv`: is a pointer to the string arguments pointer.
 *
 * By running the following command:
 * `./a.out arg1 arg2 ... argN`
 * it is possible to print all the main arguments.*/
int main(int argc, char **argv){
    for(int i=0; i<argc; i++){
        printf("%d: %s\n", i, argv[i]);
    }
}
