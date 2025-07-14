#include <stdio.h>

int main(void){
    int i = 0;
    
    /*
     * while loop is done until the condition expressed in round brackets is
     * true. In this case:
     * - The condition i<10 is checked
     * - The variable i is printed
     * - The variable i is incremented by 1
     */
    while(i<10){
        printf("%d\n",i);
        i++;
    }
    
    /*
     * for loop allows to perform the same task using a simpler syntax.
     * In the round brackets are defined:
     * - The count variable initialization (i=0)
     * - The terminal condition (i<10)
     * - The count increment (i++)
     *
     * i = 0
     * while(i<10){
     *  ...
     *  i++;
     * }
     */
    for(i=0; i<10 ; i++){
        printf("%d\n",i);
    }
    
    /*
     * Not all the arguments must be provided to the for loop.
     * As an example in this case:
     * - The variable is set to 0 outside the loop.
     * - The end condition is checked by an if statement.
     *   break is used to terminate the loop. The program continues to the next block.
     * - Increment is performed at the end of the loop.
     */
    i = 0;
    for(;;){
        if(i >= 10) break;
        printf("%d\n",i);
        i++;
    }
    
     /*
     * Modern version of C language allows to declare the count variable directly
     * in the for statement.
     * If only one instruction is provided it is not necessary to use a block.
     * It is worth to notice that if the counter is initialized inside the for
     * statement the variable cannot be used outside the loop. This causes
     * compilation error.
     */
    for(int j=0 ; j<10 ; j++) printf("%d\n",j);
    // printf("%d",j);
    
    /*
     * In this case an array of integers is initialized.
     * The loop continues until the condition a[k]!=0 is true.
     * This means that the loop terminates if the element k of the array a is 0.
     */
    int a[] = {1,6,3,4,8,0};
    int k;
    for(k=0; a[k]!=0 ; k++){
        printf("%d\n",a[k]);
    }
    
    /*
     * The goal of the following code is to check if the value 3 is in the array.
     * Suppose that the value 0 is used, by purpose, as array terminator like
     * in strings.
     *
     * The loop is terminated by the break command if the element k of the array
     * a is equal to 3.
     * It is worth to notice that the symbol == is used to check the equality condition,
     * instead of = for the assignment.
     * Knowing the array terminator, the presence of the value and its position
     * can be easily checked by if statement.
     * The value is not present if in the a array, in the loop termination index,
     * the value is equal to 0.
     *
     * This implementation can be done, only if the loop index is declared
     * outside the loop.
     */
    for(k=0 ; a[k]!=0 ; k++){
        if(a[k]==3) break;
    }
    if(a[k] == 0) printf("3 not found\n");
    else printf("3 found in position %d\n", k);

    return 0;
}
