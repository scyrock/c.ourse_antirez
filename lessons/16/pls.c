#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* The struct is used for prefixed length strings.
 * The struct is well-aligned: the first two struct elements occupy 4 bytes each.
 * The last element is a pointer, this allows to assign it by malloc() when a pls
 * is initialized.*/
struct pls{
    uint32_t len;       // string length
    uint32_t refcount;  // number of references
    uint32_t magic;     // ensure pls validation
    char str[];         // string content
};

/* Initialize a prefixed length string.
 * To improve compatibility with standard string implementation the function
 * returns the pointer to the string content. */
char *pls_create(char *init, int len){
    /* The pls dimension is equal to: the structure dimension + the string length
     * + 1 for the null terminator. */
    struct pls *p = malloc(sizeof(struct pls)+len+1);
    p->len = len;       // set pls length
    p->refcount = 1;    // set pls reference count
    p->magic = 0xDEADBEEF;

    /* Copy string content. */
    for(int i=0; i<len; i++){
        p->str[i] = init[i];
    }

    p->str[len] = 0;    // terminate the string

    return p->str;      // return the pointer to the string content
}

/* print the content of the string `s`. */
void pls_print(char *s){
    /* Shift the pointer of a value equal to the structure itself.
     * The obtained pointer is then casted to pls structure.*/
    struct pls *p = (struct pls*)(s-sizeof(*p));
    
    for(int i=0; i<p->len; i++){
        putchar(p->str[i]);
    }
    printf("\n");
}

/* Free the memory of a previously created pls. */
void pls_free(char *s){
    /* To clean the memory the function free() must receive as argument the
     * pointer returned by malloc(). For this reason the pointer `s` is shifted
     * by `struct pls`. */
    free(s-sizeof(struct pls));
}

/* Validate the pls string checking the `magic` element of `p` */
void pls_validate(struct pls *p){
    if(p->magic != 0xDEADBEEF){
        printf("ERROR: invalid string\n");
        exit(1);
    }
}

/* Reduce the pls reference counter by one. If the reference counter is zero,
 * the memory is deallocated.*/
void pls_release(char *s){
    struct pls *p = (struct pls*)(s-sizeof(*p));
    pls_validate(p);

    /* For debugging the current reference counter is printed. */
    printf("Refount, before release, is %d\n", (int)p->refcount);
    
    /* If the reference count is already zero, something went wrong.
     * An error is printed and the execution terminates by `exit(1)`*/
    if(p->refcount==0){
        printf("ERROR: aborted on free error\n");
        exit(1);
    }

    p->refcount--;      // decrease the reference counter of one
    
    /* If, after the decrease, the reference count is zero the structure memory
     * is deallocated. */
    if(p->refcount==0){
        p->magic = 0;
        pls_free(s);
        /* For debugging the current reference counter is printed. */
        printf("Refount, after pls_free(), is %d\n", (int)p->refcount);
    }
}

/* Increase the pls reference counter by one. */
void pls_retain(char *s){
    struct pls *p = (struct pls*)(s-sizeof(*p));

    /* For debugging the current reference counter is printed. */
    printf("Refount, beafore retain, is %d\n", (int)p->refcount);
    /* If the reference count is already zero, something went wrong.
     * An error is printed and the execution terminates by `exit(1)`*/
    if(p->refcount==0){
        printf("ERROR: aborted on retain of illegal string\n");
        exit(1);
    }

    p->refcount++;
}

/* Returns the pls length. */
uint32_t pls_len(char *s){
    struct pls *p = (struct pls*)(s-sizeof(*p));
    return p->len;
}

char *global_string;

int main(void){
    char *mystr = pls_create("Hello WorldHello WorldHello World", 33);
    
    /* After `mystr` is copied in `global_string`, it is necessary to use
     * pls_retain() to properly increase the reference count.*/
    global_string = mystr;
    pls_retain(mystr);

    /* `mystr` is displayed using both pls_print() and printf(). */
    pls_print(mystr);
    printf("%s %d\n", mystr, (int)pls_len(mystr));
    
    /* A reference to mystr is removed by pls_release(). */
    pls_release(mystr);
    printf("%s\n", global_string);

    /* A reference (the last) to mystr is removed by pls_release().
     * The reference count is 0, hence the memory is deallocated.*/
    pls_release(mystr);
    
    /* pls_release() is used despite the `mystr` being previously deallocated.
     * The program exits raising an error.*/
    pls_release(mystr);
    return 0;
}


