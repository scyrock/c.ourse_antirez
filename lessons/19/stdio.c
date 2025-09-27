#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>      // To use open()
#include <unistd.h>     // To use close()
#include <errno.h>

/* This program reproduces the result obtained during lesson 18, using system
 * calls instead of libc commands.*/

// See lesson 17 for more information about hexdump.
#define CHARS_PER_LINE 16
/* Given a generic pointer `p` and the related content length `len` the content
 * is displayed in a hexdump-like style.*/
void hexdump(void *p, size_t len){
    unsigned char *byte = p;
    size_t po = 0;

    for(size_t i=0; i<len; i++){
        printf("%02X ", byte[i]);
        if ( (i+1)%CHARS_PER_LINE==0 || i==(len-1) ){
            // Padding
            if ( i==(len-1) ){
                int pad = CHARS_PER_LINE - (len%CHARS_PER_LINE);
                pad = pad%CHARS_PER_LINE;
                for(int j=0; j<pad; j++) printf("~~ ");
            }
            printf("\t");   // Add tab
            // Display human-readable characters
            for(size_t j=po; j<=i; j++){
                int c = isprint(byte[j]) ? byte[j] : '.';
                printf("%c", c);
            }
            po = i+1;       // Update po
            printf("\n");   // New line
        }
    }
}

int main(void){

    /* The system call open() opens the file provided as first argument.
     * By the binary flag O_RDONLY the file is opened in read mode.
     * All the documentation about system calls can be found in section 2
     * of man (eg man 2 open).
     * The function returns the file descriptor. The file descriptor is a
     * nonnegative integer value that is an index to an entry in the process's
     * table of open file descriptors.*/
    int fd = open("stdio.c", O_RDONLY);

    /* errno variable is used to store function error values. */
    printf("The error number is: %d", errno);

    /* The value -1 is used as flag in case of errors.*/
    if(fd==-1){
        /* perror() prints the provided string, and then prints information
         * related to the error number.*/
        perror("Unable to open file");
        return 1;
    }

    char buf[32];
    ssize_t nread; //signed size_t to handle -1 in case of error.

    /* System call read() has as arguments:
     * - The file descriptor of the file to read.
     * - The buffer to fill.
     * - The buffer length.
     * The function returns the number of read bytes. If the returned value is 0
     * the file has ended. In case of errors the function returns -1.*/
    while((nread=read(fd,buf,sizeof(buf)))){
        hexdump(buf,nread);
    }

    if(nread==-1){
        perror("Reading file");
        return 1;
    }

    close(fd);

    return 0;
}
