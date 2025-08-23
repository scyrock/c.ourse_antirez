#include <stdio.h>
#include <stdlib.h>     // to use malloc()

/* Set numerator and denominator of fraction f*/
void set_fraction(int*f,int num,int den){
    f[0] = num;
    f[1] = den;
}

/* Print the fraction f*/
void print_fraction(int*f){
    printf("Numerator: %d \nDenominator: %d \n%d/%d\n\n", f[0],f[1],f[0],f[1]);
}

/* Given the fraction numerator and denominator, the function returns the
 * pointer to the fraction.
 * The function returns NULL for out of memory.*/
int *create_fraction(int num, int den){
    int* f = malloc(sizeof(int)*2);
    if (f==NULL) return NULL;       // malloc() error check
    f[0] = num;
    f[1] = den;

    return f;
}

/* Simplify the provided fraction. */
void simplify_fraction(int *f){
    /* The loop looks for a common divisor d.
     * Each time a common divisor is found the fraction is simplified.
     * The algorithm can be improved by directly looking for the
     * greatest common divisor)*/
    for(int d=2; d<=f[0] && d<=f[1]; d++){
        while(f[0]%d==0 && f[1]%d==0){
            f[0] /= d;
            f[1] /= d;
        }
    }
}
int main(void){
    /* My fraction is defined by the pointer f.
     * Pointer f has the dimension of 2 int variables on the machine
     * +--num--+--den--+
     * | 1111  |  2222 |
     * + f[0]  |  f[1] |*/
    int *f1 = malloc(sizeof(int)*2);    

    set_fraction(f1,1,2);
    print_fraction(f1);
    
    /* By create_fraction, all the operations related to memory allocation are
     * handled by the function itself.*/
    int *f2 = create_fraction(8,7);
    print_fraction(f2);
    
    int *f3 = create_fraction(45,35);
    print_fraction(f3);
    simplify_fraction(f3);
    printf("Simplified fraction:\n");
    print_fraction(f3);

    return 0;
}
