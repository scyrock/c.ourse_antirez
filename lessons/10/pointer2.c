#include <stdio.h>

int main(void){
    int x = 8;
    int *y = &x; // pointer y stores the x variable memory address.
    
    /* z is a pointer to a pointer. To do that it is needed to use ** and also
     * to specify which is the initial pointed variable. */
    int **z = &y;     
    
    /* The output of these two printf are the same.
     * In the first case the variable memory address is accessed by &.
     * In the second case the variable value is accessed by * (dereferencing).*/
    printf("x variable is stored at %p and its value is %d\n", &x, x);
    printf("x variable is stored at %p and its value is %d\n", y, *y);
    
    printf("x variable is stored at %p, y is stored at %p\n", y, z);

    /* The dimension of the pointers can be checked, as usual, by sizeof().
     * The pointer dimension is function of the machine architecture.
     * It is worth to notice usually all the pointers have the same dimension.
     *
     * Use of (int) before the expression is called casting. This ensures that
     * the value returned by sizeof is converted to int type.*/
    printf( "The dimention of x is: %d bytes.\n"
            "The dimention of y is: %d bytes.\n" 
            "The dimention of z is: %d bytes.\n", 
            (int)sizeof(x), (int)sizeof(y), (int)sizeof(z));
    
    /* Strings are stored as array of char values.
     * Array values are stored in the memory one after the other.
     * In C all the array variables are considered also as pointers.
     * Pointer p of type char stores the memory address of the first element
     * of mystr.*/
    char mystr[] = "Hello World";
    char *p = mystr;
    
    /* The equivalence between the C array variable and the corresponding
     * pointer is proved by the following example.*/
    printf("At adress %p there is stored the string: %s\n",mystr, mystr); 
    printf("At adress %p there is stored the string: %s\n",p, p);
    
    /* By dereferencing it is possible to access all the string values.
     * * allows to access only the first element of the pointer.
     * By [] it is possible to access also the next ones.*/
    printf("The first string element is: %c\n", p[0]);
    printf("The fourth string element is: %c\n", p[3]);

    /* Due to the fact that pointers are just integer values, they can be
     * manipulated by standard algebra.
     * As an example in this case, before accessing the value by *, the pointer
     * is increased by 3.*/
    printf("The first string element is: %c\n", *p);
    printf("The fourth string element is: %c\n", *(p+3));
    
    /* p2 stores the memory address of string char.
     * The pointer p2 has "wrong" type, despite mystr2 type is char the pointer
     * is type short. To avoid warning casting is performed (short*).
     *
     * The printed value is 16705.
     * The short pointer returns the first two bytes of mystr2 that represent AA.
     * In ASCII A is represented by 41.
     * *p2 is equal to 0x4141 that is the hexadecimal representation of 16705.*/
    char mystr2[] = "AABBCCDDEEFF";
    short *p2 = (short*)mystr2;
    printf("%d\n", *p2);
    
    /* p2++ increases the pointer value.
     * Despite it is expected to print BA > 4142 > 0x4142 > 16961 it is printed
     * 16962, that corresponds to BB > 4242 > 0x4242 > 16962.
     *
     * This happens because by default when a pointer is incremented, the increment
     * is multiplied by the length of the pointer type. In this case due to the fact
     * that the pointer refers to a short, the increment is two, for this reason
     * p2++ skips one value.*/
    p2++;
    printf("%d\n", *p2);
    
    /* += is a compact form to increase the value by 3. This notation can be used
     * also with other math operators, such as /= *=.
     *
     * In this case *p2 is EE > 0x4545 > 17733.
     * */
    p2 += 3;
    printf("%d\n",*p2);
    
    /* C does not care about the fact that the pointer should be outside the range
     * of the program memory. The program could return random values accessed in
     * the memory, or fail by segmentation fault. */
    p2 += 100;
    printf("%d\n",*p2);
    
    /* Given a string (mystr3), and its pointer (p3), it is possible to print the
     * string char one-by-one. 0 is used to check the string end. putchar instead
     * allows to print in the terminal a single char value.
     *
     * At the end of the string print, the value stored in p3 is increased by
     * the length of mystr3.*/
    char mystr3[] = "AABBCCDDEEFF";
    char *p3 = mystr3;
    
    printf("At the begin p3 is %p \n", p3);
    printf("The memory adress %p in decimal is %lu \n", p3, (unsigned long)p3);
    while (*p3 != 0){
        putchar(*p3);
        p3++;
    }
    printf("\nAt the end p3 is %p \n", p3);
    
    /* Dereferencing allows to use the same approach with flexibility.
     * In this case the value after the pointer is printed. This allows to
     * skip the first value and print the termination value.
     */
    char mystr4[] = "AABBCCDDEE.FF";
    char *p4 = mystr4;

    while (*p4 != '.'){
        putchar(p4[1]);
        p4++;
    }
    printf("\n");
    

    return 0;
}
