#include <stdio.h>
#include <stdlib.h>     // to use malloc()
/* All the code previously designed in fraction.c, can be easily adapted to
 * the struct fract, by simply:
 * - Change fraction variables declaration
 * - Substitute pointers to num and den (f[0], f[1]) with the structure
 *   syntax (f->num, f->den). */


/* By struct aggregated data can be manipulated.
 * In this case the structure `fract` is composed by two integers, the first one
 * is called `num`, and the second one `den`
 *
 * Internal layout
 * +----+----+
 * |num | den|
 * +----+----+
 * */
struct fract{
    int num;
    int den;
};

/* Inside the structure variable types of different dimensions can be located.
 * In this case, as an example, an unsigned char is added.
 * +----+----+----+
 * |cPPP|num | den|
 * +----+----+----+
 */
struct fract_c{
    unsigned char color;
    int num;
    int den;
};

/* Print the fraction f*/
void print_fraction(struct fract *f){
    printf("Numerator: %d \nDenominator: %d \n%d/%d\n\n", f->num,f->den,f->num,f->den);
}

/* Given the fraction numerator and denominator, the function returns the
 * pointer to a fract structure.
 * The function returns NULL for out of memory.*/
struct fract *create_fraction(int num, int den){
    struct fract *f = malloc(sizeof(struct fract));
    if (f==NULL) return NULL;       // malloc() error check
    f->num = num;
    f->den = den;

    return f;
}

/* Simplify the provided fraction. */
void simplify_fraction(struct fract *f){
    /* The loop looks for a common divisor d.
     * Each time a common divisor is found the fraction is simplified.
     * The algorithm can be improved by directly looking for the
     * greatest common divisor)*/
    for(int d=2; d<=f->num && d<=f->den; d++){
        while(f->num%d==0 && f->den%d==0){
            f->num /= d;
            f->den /= d;
        }
    }
}
int main(void){
    /* The dimension of `fract` is 8 bytes, that is coherent with its content
     * (e.g. 2 int variables.)*/
    printf("The dimention of struc `frac` is %d\n", (int)sizeof(struct fract));
    
    /* The dimension of `fract_c` is not coherent with its content (e.g. 1 char
     * and 2 int). This is due to the fact that, by default, struct ensures that
     * the address of each struct element is multiple of its dimension.*/
    printf("The dimention of struc `frac_c` is %d\n", (int)sizeof(struct fract_c));
    
    /* Structures are initialized as any standard variable type.
     * Structures are custom data types defined by the user.*/
    struct fract f;
    
    /* Dot allows to access the structure elements. */
    f.num = 1;
    f.den = 2;
    printf("%d, %d\n", f.num, f.den);
    
    /* Pointer `p` points to the struct f.*/
    struct fract *p = &f;

    /* To access structure values by the pointer `->` is used.*/
    p->num = 3;
    p->den = 4;
    printf("%d, %d\n", f.num, f.den);
    
    /* From fraction.c */
    struct fract *f2 = create_fraction(8,7);
    print_fraction(f2);

    struct fract *f3 = create_fraction(45,35);
    print_fraction(f3);
    simplify_fraction(f3);
    printf("Simplified fraction:\n");
    print_fraction(f3);

    return 0;
}
