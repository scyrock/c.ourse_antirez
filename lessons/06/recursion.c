#include <stdio.h>

void count(int start, int end){
    /*
     * Function count prints numbers from start to end
     * Parameters   - int start: initial number to count
     *              - int end: end number to count
     */

    /*
     * The following implementation avoids the use of label, goto and while.
     * This solution is not memory efficient, at each instance new variables are allocated.
     * This is proven by the variable memory address, which changes at each instance.
     */
    printf("The start variable pointer is: %p\n", &start);
    printf("The end variable pointer is: %p\n\n", &end);
    if (start>end) return; // if start number is greater than end, the function terminates
    printf("%d\n", start); // the start number is printed
    
    /*
     * The function is recursively called, increasing the starting number by one.
     * In the new instance of count function the value is increased by one
     * compared to the previous instance.
     * The recursion terminates when the condition (start>end) is true.
     */
    count(start+1,end);
}

int main(void){
    count(0,9);
}
