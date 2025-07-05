/*
 * Function declaration for printf without including stdio.h
 * This demonstrates that it is possible to declare functions manually
 * instead of use libraries.
 */
int printf(const char * restrict format, ...);

int main(void){

    printf("Hello world\n");

    return 1;

}
