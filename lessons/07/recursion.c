#include <stdio.h>

void count_vanilla(int start, int end){
    if (start>end) return; 
    printf("%d\n", start);    
    count_vanilla(start+1,end);
}

void count(int start, int end){
    /*
     * The functionality implemented by count is the same as count_vanilla.
     * Despite that, in this case, thanks to goto the generation of a
     * computationally inefficient recursion is avoided.
     * The variable start is updated, and, as shown by pointer value no
     * new variables are generated at each iteration.
     * This represents a quite standard solution to properly implement
     * recursion in C.
     */
iterate:
    if (start>end) return; 
    printf("%d - ", start);
    printf("The start variable pointer is: %p\n", &start);
    start = start + 1;
    goto iterate;
}

int main(void){
    count(0,9);

    return 0;
}
