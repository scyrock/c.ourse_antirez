#include <stddef.h>
#include <stdio.h>
/* In C, the use of functions with a variable number of arguments is handled by
 * the library stdarg.h. */
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

/* Prints a variable list of arguments based on a format string.
 * `fmt` defines the argument types: 'i' for int, 's' for char*.
 * `...` represents the variable arguments corresponding to the format string. */
void foo(char *fmt, ...){
    va_list ap;         // list of arguments (argument pointer)

    /* The va_start() macro initializes ap for subsequent use by va_arg() and
     * va_end(). It must be called first. The argument 'fmt' is the name of the
     * last fixed argument before the variable argument list starts.  */
    va_start(ap, fmt);

    char *p = fmt;
    /* Each call to va_arg() modifies `ap` so that the next call returns the
     * next argument. The expected type (int, char*, etc.) must be specified. */
    while (*p) {                // loop on each char of the format string
        if(*p == 'i'){          // integer
            int i = va_arg(ap, int);
            printf("%d\n", i);
        } else if (*p == 's') { // string
            char *s = va_arg(ap, char*);
            printf("%s\n", s);
        } else {                // unknown specifier
            printf("Wrong specifier.\n");
            goto cleanup;
        }
        p++;    // next type specifier
    }

// The goto label is used here to ensure va_end is always called before exiting.
cleanup:
    /* Each invocation of va_start() must be matched by a corresponding
     * invocation of va_end() in the same function. After the call va_end(ap)
     * the variable ap is undefined */
    va_end(ap);
}

void bar(const char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    /* The functions vprintf(), vfprintf(), vdprintf(), vsprintf(), vsnprintf()
     * are equivalent to the functions printf(), fprintf(), dprintf(), sprintf(),
     * snprintf(), respectively, except that they are called with a va_list
     * instead of a variable number of arguments. */
    vprintf(fmt, ap);
    va_end(ap);
}

void bar2(const char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    char mybuf[32];
    /* vsnprintf writes formatted output to a buffer with a size limit. */
    vsnprintf(mybuf, sizeof(mybuf), fmt, ap);
    va_end(ap);

    // Print the original content stored in `mybuf`
    printf("%s\n", mybuf);
    for(int j=0; j<sizeof(mybuf); j++){
        /* If c is an uppercase letter, tolower() returns its lowercase
         * equivalent, if a lowercase representation exists in the
         * current locale. */
        mybuf[j] = tolower(mybuf[j]);
    }
    printf("%s\n", mybuf);
}

/* Prints formatted text centered within an 80-character wide terminal line. */
void bar3(const char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    char mybuf[32];
    vsnprintf(mybuf, sizeof(mybuf), fmt, ap);
    va_end(ap);

    size_t len = strlen(mybuf);
    // Find the padding as a function of the terminal width (80)
    size_t padding = (80-len)/2;

    for(size_t j=0; j<padding; j++) printf(" ");
    printf("%s\n", mybuf);
}

int main(void){
    // Proper use of foo() with matching format specifiers
    foo("iisi", 10, 20, "hello hello", 8);

    // Wrong/unknown type specifier 'X' in format string
    foo("iiXsi", 10, 20, "hello hello", 8);

    // Mismatch between type specifier and arguments
    // foo("iisi", "cat", 10, 20, "hello hello", 8);
    printf("\n");

    bar("%d %d %s %d", 10, 20, "hello hello", 8);
    printf("\n\n");

    bar2("%d %d %s %d", 10, 20, "HELLO WORLD", 8);
    printf("\n");

    bar3("%d %d %s %d", 10, 20, "hello hello", 8);
    return 0;
}
