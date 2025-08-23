#include <stdio.h>

struct fract{
    int num;
    int den;
};

/* Print the fraction f. */
void print_fraction(struct fract *f){
    printf("Numerator: %d \nDenominator: %d \n%d/%d\n\n", f->num,f->den,f->num,f->den);
}

/* Given the fraction numerator and denominator, the function returns
 * a fract structure. */
struct fract create_fraction(int num, int den){
    struct fract f;
    f.num = num;
    f.den = den;

    return f;
}

/* Simplify the provided fraction. */
void simplify_fraction(struct fract *f){
    for(int d=2; d<=f->num && d<=f->den; d++){
        while(f->num%d==0 && f->den%d==0){
            f->num /= d;
            f->den /= d;
        }
    }
}
int main(void){
    /* The function create_fraction returns a struct variable.
     * In this case at the end of the function execution the output value is
     * copied in the variable f1.*/
    struct fract f1 = create_fraction(10,20);
    
    /* The other functions receive as argument the pointer to the fract structure.*/
    print_fraction(&f1);
    simplify_fraction(&f1);
    print_fraction(&f1);
    return 0;
}
