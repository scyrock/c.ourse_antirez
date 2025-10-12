#include <stdio.h>
#include <string.h>

/* The structure foo, in a 64-bit system has the following memory layout:
 *
 * +-------------------------------+-------------------------------+
 * |            4-bytes            |            4-bytes            |
 * +---1---|---2---|---3---|---4---+---5---|---6---|---7---|---8---+
 * |               i               | a[1]  |  a[2] | a[3]  |  a[4] |
 * +-------------------------------+-------------------------------+
 * ^
 * `foo` memory address
 *
 * */
struct foo{
    int i;
    unsigned char a[4];
};

/* By using union, all fields of the structure start at the same memory address.
 * +-------------------------------+
 * |            4-bytes            |
 * +---1---|---2---|---3---|---4---+
 * |               i               |
 * +===============================+
 * | a[1]  |  a[2] | a[3]  |  a[4] |
 * +-------------------------------+
 * ^
 * `bar` memory address
 *
 * */
struct bar{
    union{
        int i;
        unsigned char a[4];
    };
};

int main(void){
    /* foo init */
    struct foo f;
    f.i = 10;
    memcpy(f.a,"abcd",4);

    printf("foo.i = %d, foo.a[2] = %d\n", f.i, f.a[2]);

    /* bar init*/
    struct bar b;
    b.i = 10;
    /* The two structure fields share the same memory address, for this reason,
     * they share the same value.*/
    printf("bar.i = %d, bar.a = [%d %d %d %d]\n", b.i, b.a[0], b.a[1], b.a[2], b.a[3]);

    /* union is very useful when a function could accept, alternatively,
     * different kinds of arguments. In this way, given the same amount of memory,
     * the memory layout can be customized as a function of the argument (int,
     * string, array, etc.)*/

    return 0;
}
