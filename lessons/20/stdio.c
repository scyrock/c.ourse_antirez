#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void){
    printf(">>> Test 1 <<<\n");
    /* Despite the printf() being before the sleep() the text is printed after the
     * sleeping time. This behaviour is due to the fact that printf() bufferizes
     * the input: it collects the text to print in a buffer and displays when certain
     * conditions are effective. */
    printf("Hello world");
    sleep(3);   // The process waits 3 seconds

    printf("\n\n>>> Test 2 <<<\n");
    /* One of the conditions that trigger the printf() to display the buffer text
     * is the presence of a new line. In this second case, as an example, the
     * text is printed before the waiting time.*/
    printf("Hello world\n");
    sleep(3);

    printf("\n>>> Test 3 <<<\n");
    /* By using the system call write(), printf() buffering is bypassed.
     * The function write has as arguments:
     * - The file descriptor >  STDOUT_FILENO, the default one to write
     *   in the terminal.
     * - The pointer to the content to write. > The next string character.
     * - The length of the content to write > 1 byte.
     *
     * The drawback of this approach is that to print a string, it is necessary
     * to perform many system calls. On the contrary libc commands, such as
     * printf() or putchar() try to optimize this process by buffering. They
     * collect the content to display, and when certain conditions are fulfilled
     * (eg new line, full buffer) a single system call is used to display the
     * content.*/
    char *mystr = "Hello world";
    size_t len = strlen(mystr);
    for(size_t i=0; i<len; i++)
        write(STDOUT_FILENO, mystr+i, 1);
    sleep(3);

    printf("\n\n>>> Test 4 <<<\n");
    /* The command fflush(), displays the buffer content and cleans the buffer.
     * In this way, it is ensured that the content is displayed.*/
    for(size_t i=0; i<len; i++)
        putchar(mystr[i]);
    fflush(stdout);
    sleep(3);

    /* Combining the previous commands a simple animation is created.*/
    printf("\n\n>>> Test 5 <<<\n");
    for(size_t i=0; i<len; i++){
        putchar(mystr[i]);
        fflush(stdout);
        usleep(100000);     // Waiting time in micro-seconds
    }
    printf("\n");
    /* libc functions ensure code portability between different machines. This
     * is ensured thanks to C language standardization.
     * On the contrary the use of system calls, that allow deeper control on
     * software execution, may raise issues due to the fact that different machines
     * (eg operating systems) may not share the same system calls.*/

    return 0;
}
