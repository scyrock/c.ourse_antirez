#include <stdio.h>
#include <ctype.h>

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
    /* FILE could be a variable type defined by typedef in the stdio library.
     * The function fopen() opens the file stdio.c in read mode (`r`) and
     * returns the pointer to a structure (fp) that contains all the information
     * about the opened file.*/
    FILE *fp = fopen("stdio.c","r");
    
    /* The special pointer NULL is used to notify the failure of the open process.*/
    if(fp==NULL){
        printf("Unable to open the file\n");
        return 1;
    }
    
    /* To read the file the function fread() is used.
     * The function has the following arguments:
     * - A pointer to a buffer, in which the read file values are stored.
     *   In this case the buffer has a length of 32. (Please note that in C an
     *   array variable is also the pointer to the array).
     * - The number of items to read.
     * - The length of the buffer.
     * - The pointer to the file.
     * The function returns the number of bytes read from the file. */
    
    char buf[32];
    size_t nread;
    
    /* The file reading is terminated when the file ends (eg when fread doesn't
     * read any byte.)*/
    while((nread=fread(buf,1,sizeof(buf),fp))){ 
        /* By hexdump it is possible to display the read bytes.*/
        hexdump(buf,nread);
    }
    
    /*fclose() closes the file opened by fopen().*/
    fclose(fp);
}
