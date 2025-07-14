#include <stdio.h>

int main(void){
    /*
     * switch is similar to a cascade of if statements.
     * default condition is executed if all the others fail.
     */
    int i = 5;

    switch(i){
    case 5: printf("It is a five\n"); break;
    case 6: printf("It is a six\n"); break;
    default: printf("It is another number\n"); break;
    } 
    
    if(i==5) printf("It is a five\n");
    else if(i==6) printf("It is a six\n");
    else printf("It is another number\n");
    
    /*
     * Each case can execute multiple instructions.
     * break terminates the switch execution. If break is not present the program
     * continues the execution. This means that following cases are executed up to
     * find a break.
     * Inside a switch case it is not possible to declare variables.
     * case has a similar implementation to goto labels. Compiler can exploit
     * different solutions to compile switch.
     */
    switch(i){
     case 5: 
         // int j = 7
         printf("It is a five\n");
         printf("Oh yes it is exactly five\n");
         // break;
     case 6: 
         printf("It is a six\n"); break;
     default: 
         printf("It is another number\n"); break;
     }
    
    /*
     * blocks allow to declare variables inside the switch case.
     * In this case a block is used in case 5 to have the variable j.
     */
    switch(i){
      case 5:
          {
            int j = 7;
            printf("It is a five\n");
            printf("Variable j is equal to %d\n", j);
            break;
          }
      case 6:
          printf("It is a six\n"); break;
      default:
          printf("It is another number\n"); break;
      }

    return 0;
}
