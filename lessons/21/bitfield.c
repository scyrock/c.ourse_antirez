#include <stdio.h>

/* By bitfield it is possible to specify the dimension, in bits, of each element
 * of the structure. In this case `a` and `b` have dimension of 4 bits,
 * instead `c` has dimension of 8 bits. Structure `foo` has dimension of
 * (4+4+8) = 16 bits = 2 bytes*/
struct foo{
    unsigned char a:4;
    unsigned char b:4;
    unsigned char c:8;
};

int main(void){
    struct foo f;
    f.a = 7;
    /* The field `b` of structure `foo` has a maximum dimension of 4 bits.
     * This means that it could store values between 0 and 2^4-1 (15).
     * As also highlighted by the compiler the value 28 is wrapped
     * (eg. 28%(2^4) = 12). In C this behaviour is ensured only for unsigned
     * types. For signed variables (eg int, char, etc) it is an undefined behaviour.*/
    f.b = 28;
    f.c = 167;

    printf("Struct f has dimension: %zu bytes\n", sizeof(f));
    printf("f.a = %d\nf.b = %d\nf.c = %d\n", f.a, f.b, f.c);

    /* By bitfield it is possible to optimize memory allocation, and in some cases
     * to unify the memory layout to some communication protocol. Unfortunately
     * bitfield is not completely standardized in C, this may generate some
     * unexpected behaviour between different machines.*/

    return 0;
}
