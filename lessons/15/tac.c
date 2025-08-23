#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* To test the program you can run `./a.out tac.c` */

/* line is a linked list.
 * Each structure contains the content and the reference to the next value.*/
struct line{
    char *s;            // store the line content
    struct line *next;  // point to the next line structure
};

int main(int argc, char **argv){
    /* If the program is executed without any argument, the program terminates
     * returning 1 and prints an error message.*/
    if(argc!=2){
        printf("ERROR: Missing file name.\n");
        return 1;
    }
    
    /* A pointer of type FILE is initialized.
     * The pointer is initialized by fopen() that has as arguments:
     * - The file name path, in this case provided as program argument
     * - The open mode, in this case "r", that means that the file is opened in
     *   read only mode.*/
    FILE *fp = fopen(argv[1],"r");
    
    /* Check fopen() execution. */
    if (fp==NULL){
        printf("ERROR: File does not exist.\n");
        return 1;
    }
    
    /* buf is a char variable used to temporarily store the line of the file.*/
    char buf[1024];

    /* Initialize the list head*/
    struct line *head = NULL;

    /* fgets() reads line by line from the file. fgets() has as arguments:
     * - The buffer in which to store the read line.
     * - The buffer length.
     * - The file pointer from which to read the line.
     *
     * fgets() is executed until it returns NULL, this means that there
     * are no more lines to read in the file.*/
    while(fgets(buf,sizeof(buf),fp)!=NULL){
        /* `l` is a struct line that stores:
         * - The line content memory address.
         * - The memory address of the next line structure.*/
        struct line *l = malloc(sizeof(struct line));
        size_t linelen = strlen(buf);

        /* A memory block equal to the string length+1 (to store string
         * terminator) is allocated. The memory address of this block is stored
         * in the element `s` of structure `l` */
        l->s = malloc(strlen(buf)+1);
        
        /* The buffer content is copied, value by value in the structure. */
        for(size_t i=0; i<linelen+1; i++){
            l->s[i] = buf[i];
        }

        l->next = head;
        head = l;   // head is updated with the new last line.
    }

    /* Close the file opened by fopen() */
    fclose(fp);
    
    /* Through the linked list the while loop iterates until it reaches the NULL value.
     * At each iteration the line content is printed and the head is updated
     * with the next line to print.*/
    while(head!=NULL){
        printf("%s",head->s);
        head = head->next;
    }

    return 0;
}
