#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* The qsort() function sorts an array with n elements.
 * The contents of the array are sorted in ascending order according to a
 * comparison function pointed to by `compar`, which is called with two
 * arguments that point to the objects being compared.
 * The comparison function must return an integer less than, equal to,
 * or greater than zero if the first argument is considered to be respectively
 * less than, equal to, or greater than the second. If two members
 * compare as equal, their order in the sorted array is undefined.
 *
 * For more informations refers to `man 3 qsort`.*/

/* Given the two arguments pointer the values are compared, and an integer value
 * is returned as a function of the qsort() indications.
 * if(a>b)   >0
 * if(a==b)   0
 * if(a<b)   <0
 *
 * `const` ensures that the value stored at the pointer memory address is not
 * modified by the function.*/
int compare_int_overflow(const void *a, const void *b){
    const int *ap = a;
    const int *bp = b;

    /* Despite this approach being simple and concise, it is prone to overflow.
     * If the difference between the compared values is out of the `int` range,
     * undefined behavior occurs.*/
    return *ap-*bp;
}
/* To avoid undefined behavior, if statements can be used.*/
int compare_int(const void *a, const void *b){
    const int *ap = a;
    const int *bp = b;
    if(*ap>*bp) return  1;
    else if(*ap<*bp) return  -1;
    else return 0;
}

int main(void){
    int a[10];

    /* Generate an array of integer pseudo-random numbers.
     * By `&15` the obtained value are saturated to 15. This because 15 in
     * binary is 1111. By `rand()&15` only the last 4 bits of `rand()` are
     * assigned to `a[i]`.
     * It is worth noting that the function rand() returns pseudo-random integers.*/
    for(int i=0; i<10; i++) a[i] = rand()&15;
    /* To trigger overflow, some values in the array are replaced with the
     * maximum and minimum values that can be stored in an integer variable.*/
    a[0] = INT_MAX;
    a[1] = INT_MIN;
    // Display the a array.
    for(int i=0; i<10; i++) printf("%d ", a[i]);
    printf("\n\n");

    /* Compare function with potential undefined behavior.*/
    qsort(a,10,sizeof(int),compare_int_overflow);
    // Display sorted array.
    for(int i=0; i<10; i++) printf("%d ", a[i]);
    printf("\n\n");

    qsort(a,10,sizeof(int),compare_int);
    // Display properly sorted array.
    for(int i=0; i<10; i++) printf("%d ", a[i]);
    printf("\n\n");
    return  0;
}
