#include <stdio.h>

int main(void){
    /*
     * C natively supports arrays.
     * To initialize an int array it is needed to:
     * - define the dimension, by square brackets []
     * - initialize the values by curly brackets {}
     */
    int a[8] = {1,1,2,3,5,8,13,21};
    
    /*
     * It is possible to access array value by index using square brackets []
     */
    printf("%d\n", a[4]);
    printf("%d - %d -  %d\n", a[4], a[1], a[2]);

    /*
     * Strings in C are arrays of type char.
     * The definition follows the same rules of integer arrays.
     * To terminate the string the null terminator 0 is used. This identifies the
     * end of the string and ensures that the system exactly knows when the string ends.
     *
     * In char type '0' and 0 are two different values:
     * - '0' is converted to the integer value of 48, following the ASCII convention.
     * - 0 operates as null terminator.
     */
    char str_hello[6] = {'h','e','l','l','o',0};
    printf("%s\n",str_hello);
    
    /*
     * The strings are arrays of chars.
     * For this reason a string can be printed by a simple while loop.
     * - The index i is initialized to 0.
     * - The while loop continues up to the null terminator
     * - The i element of the string is appended to the printf buffer
     * - When the index is equal to 5, the value 0 is found (null terminator),
     * - The while loop terminates
     * - The new line character (\n) is appended to the printf buffer
     * - The text is printed
     */
    int i = 0;
    while(str_hello[i] != 0){
        printf("%c", str_hello[i]);
        i++;
    }
    printf("\n");
    
    /*
     * String (char array) can be also directly defined using double quotes.
     * It is important to take into account during the length initialization also
     * the presence of the null terminator (number of characters +1).
     */
    char h[6] = "Hello";
    char w[6] = "world";
    printf("%s %s\n", h, w);

    /*
     * It is possible to initialize the string without providing the string length.
     * The memory dimension can be assessed by sizeof(). It is worth noting that
     * the sizeof() function does not operate at run time but during the compilation
     * process. This means that sizeof() does not require resources at run-time.
     */
    char h2[] = "hello";
    printf("%s\n", h2);
    printf("The h2 variable length is: %lu bytes\n", sizeof(h2));
   
    //*
     * Strings can be manipulated as a standard array. Their values can be
     * accessed and manipulated.
     */
    h2[2] = 'X';    // Second value is set to X
    h2[3] = 65;     // Third value is set to 65 (A in ASCII)
    h2[4]++;        // Fourth value is set to the next one in ASCII (o > p)
    printf("%s\n", h2);
    
    /*
     * In this case the string y has not the null terminator.
     * This generates unexpected behavior, because the end of the string is not
     * unequivocally defined.
     */
    int x = 31;
    char y[] = {'h','e'};
    int z = 32;
    printf("The expected output should be: he\n");
    printf("%s\n",y);


    return 0;
}
