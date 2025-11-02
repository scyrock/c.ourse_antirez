/* This code implements a toy version of Forth. More information can be found:
 * https://en.wikipedia.org/wiki/Forth_(programming_language) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*=========================== Data structures ==================================*/

/* In the following the different toy forth object types are defined.
 * Each token has its own type.*/
#define TFOBJ_TYPE_INT 0
#define TFOBJ_TYPE_STR 1
#define TFOBJ_TYPE_BOOL 2
#define TFOBJ_TYPE_LIST 3
#define TFOBJ_TYPE_SYMBOL 4

typedef struct tfobj{
    int refcount;
    // TFOBJ_TYPE_*
    int type;           // token type (int, str, bool, ...)
    union{              // collect the token data
        int i;          // int and bool
        struct{         // string
            char *ptr;
            size_t len;
        } str;
        struct{         // list of tokens
            // `ele` is the pointer to an array of `tfobj` pointers
            struct tfobj **ele;
            size_t len;
        } list;
    };
} tfobj;

typedef struct tfparser{
    char *prg;  // The program to compile in a list.
    char *p;    // The next token to parse.
} tfparser;

/* Define the execution context.
 * Allows to execute multiple toyforth interpreters in parallel, collecting for
 * each of them the execution information.*/
typedef struct tfctx{
    tfobj *stack;   // executed stack

} tfctx;

/*=========================== Allocation wrappers ==============================*/

/* Wraps the `malloc` function, handling out of memory errors. */
void *xmalloc(size_t size){
    void *ptr = malloc(size);
    if(ptr==NULL){
        fprintf(stderr, "Out of memory allocating %zu bytes\n", size);
        exit(1);
    }
    return ptr;
}

/*========================= Object related functions ===========================*/

/* Initializes the common fields of a generic `tfobj`. */
tfobj *createObject(int type){
    tfobj *o = xmalloc(sizeof(tfobj));
    o->type = type;
    o->refcount = 1;
    return  o;
}

/* Initializes string `tfobj`.*/
tfobj *createStringObject(char *s, size_t len){
    tfobj *o = createObject(TFOBJ_TYPE_STR);
    o->str.len = len;
    o->str.ptr = s;
    return  o;
}
/* Initializes symbol `tfobj`.*/
tfobj *createSymbolObject(char *s, size_t len){
    tfobj *o = createStringObject(s,len);
    o->type = TFOBJ_TYPE_SYMBOL;
    return o;
}
/* Initializes int `tfobj`.*/
tfobj *createIntObject(int i){
    tfobj *o = createObject(TFOBJ_TYPE_INT);
    o->i = i;
    return  o;
}
/* Initializes bool `tfobj`.*/
tfobj *createBoolObject(int i){
    tfobj *o = createObject(TFOBJ_TYPE_BOOL);
    o->i = i;
    return  o;
}
/* Initializes an empty list `tfobj`.*/
tfobj *createListObject(void){
    tfobj *o = createObject(TFOBJ_TYPE_LIST);
    o->list.ele = NULL;
    o->list.len = 0;
    return  o;
}
/*===================================== Main ===================================*/

int main(int argc, char **argv){
    /* By default the first element of argv is the program binary itself.
     * We expect to have 2 arguments: the toyforth compiler binary itself and
     * the toyforth code to compile.*/
    if (argc!=2){
        fprintf(stderr,"Usage: %s <filename>\n", argv[0]);
        return  1;
    }

    /* Given the program text, `compile` returns the `tfobj`.*/
    // tfobj *prg = compile(prgtext);
    // exec(prg);

    return  0;
}
