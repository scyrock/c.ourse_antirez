#include <stdio.h>

int main(void){
    /* The main function: 
     * return as output an intager value
     * recive as input nothing (void). (In modern version of c void should be omitted) */
    printf("Hello World\n");
    return 0;
    /* As any function also the main function has a return value. Usually the value 0 indicate a succesful software execution.
     * To visulize the returning value the following command can be used `./a.out; echo $?`.
     * This convention can be useful to concatenate the execution of different commad (e.g. `./a.out && ls`). */
}

/* Add the flag -W -Wall to gcc command allow to recive warnings during
 * the code compialtion.
 */
