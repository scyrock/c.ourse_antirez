#include <stdio.h>

int main(void){
    /*
     * In C all variables must be declared with their type before use.
     * - Declaration: reserves memory and associates a name with a type
     * - Initialization: assigns an initial value during declaration
    */

    int a = 3;      // Declaration with initialization
    int b = 8;
    int c = a+b;    // Declaration with computed initialization
    
    /*
     * Declaration and initialization could be separated as follow
     */
    // int a,b,c;
    // a = 3
    // b = 8
    // c = a+b
    
    printf("The sum is: %d\n", c);
    return 0;

}
