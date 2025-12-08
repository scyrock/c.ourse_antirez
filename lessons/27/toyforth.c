/* This code implements a toy version of Forth. More information can be found:
 * https://en.wikipedia.org/wiki/Forth_(programming_language) */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

/*=========================== Data structures ================================*/

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

/* Function table entry: each entry represents a function/word and its
 * implementation. */
struct tfctx;
typedef struct FunctionTableEntry{
    tfobj *name;
    // Pointer to native C function
    void (*callback) (struct tfctx *ctx, tfobj *name);
    // Used to store user-defined implementation function as a tf list
    tfobj *user_func;
} tffuncentry;

struct FunctionTable{
    tffuncentry **func_table;
    size_t func_count;
};

/* Define the execution context.
 * Allows to execute multiple toyforth interpreters in parallel, collecting for
 * each of them the execution information.*/
typedef struct tfctx{
    tfobj *stack;   // Executed stack
    struct FunctionTable functable;
} tfctx;

/*=========================== Functions prototypes ===========================*/
void retain(tfobj *o);
void release(tfobj *o);

/*=========================== Allocation wrappers ============================*/

/* Wraps the `malloc` function, handling out of memory errors. */
void *xmalloc(size_t size){
    void *ptr = malloc(size);
    if(ptr==NULL){
        fprintf(stderr, "Out of memory allocating %zu bytes\n", size);
        exit(1);
    }
    return ptr;
}

/* Wraps the `realloc` function, handling out of memory errors. */
void *xrealloc(void *oldptr,size_t size){
    void *ptr = realloc(oldptr, size);
    if(ptr==NULL){
        fprintf(stderr, "Out of memory allocating %zu bytes\n", size);
        exit(1);
    }
    return ptr;
}

/*========================= Object related functions =========================*/

/* Initializes the common fields of a generic `tfobj`. */
tfobj *createObject(int type){
    tfobj *o = xmalloc(sizeof(tfobj));
    o->type = type;
    o->refcount = 1;
    return  o;
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

/* Free memory allocated to a tf object. */
void freeObject(tfobj *o){
    switch(o->type){
        case TFOBJ_TYPE_LIST:
            /* Recursively release all list elements.
             * Note that the inner elements are released (decrementing their refcount),
             * and if their refcount reaches zero, they are freed. */
            for(size_t j=0; j<o->list.len; j++){
                release(o->list.ele[j]);
            }
            break;
        case TFOBJ_TYPE_SYMBOL:
        case TFOBJ_TYPE_STR:
            // Free the tf object content.
            free(o->str.ptr);
    }
    free(o);
}

/* Increase tfobj refcount. */
void retain(tfobj *o){
    o->refcount++;
}

/* Decrease tfobj refcount. */
void release(tfobj *o){
    // Check actual refcount
    assert(o->refcount>0);
    o->refcount--;

    // If the refcount is zero tjobj is deleted
    if(o->refcount == 0) freeObject(o);
}

/* Print the given object. */
void printObject(tfobj *o){
    /* Given the tf type, a properly print is implemented.
     * TFOBJ_TYPE_LIST are printed by recursive execution of the function.*/
    switch (o->type) {
        case TFOBJ_TYPE_INT:
            printf("%d", o->i);
            break;
        case TFOBJ_TYPE_LIST:
            printf("[");
            for(size_t j=0; j < o->list.len; j++){
                tfobj *ele = o->list.ele[j];
                printObject(ele);
                if(j<(o->list.len-1)) printf(" ");  // Print space
            }
        printf("]");
        break;
        case TFOBJ_TYPE_STR:
        printf("\"%s\"", o->str.ptr);
            break;
        case TFOBJ_TYPE_SYMBOL:
            printf("%s", o->str.ptr);
            break;
        default:
            printf("?");
        break;
    }
}

/*================================= String object ============================*/

/* Initializes string `tfobj`.*/
tfobj *createStringObject(char *s, size_t len){
    tfobj *o = createObject(TFOBJ_TYPE_STR);
    o->str.ptr = xmalloc(len+1);    // Allocate the memory.
    o->str.len = len;
    memcpy(o->str.ptr, s, len);     // Copy the string in the tfobj
    o->str.ptr[len] = 0;
    return  o;
}

/* Initializes symbol `tfobj`.*/
tfobj *createSymbolObject(char *s, size_t len){
    tfobj *o = createStringObject(s,len);
    o->type = TFOBJ_TYPE_SYMBOL;
    return o;
}

/* Compare two string tfobj `a` and `b` and returns:
 * 0 if `a`==`b`
 * 1 if `a`>`b`
 *-1 if `a`<`b`*/
int compareStringObject(tfobj *a, tfobj *b){
    // Find minimum str len by ternary operator
    size_t minlen = a->str.len < b->str.len ? a->str.len : b->str.len;

    /* The memcmp() function returns an  integer less than, equal to, or greater
     * than zero if  the first n bytes of s1 is found, respectively, to be less
     * than, to match, or be greater than the first n bytes of s2. */
    int cmp = memcmp(a->str.ptr, b->str.ptr, minlen);

    // If the first `minlen` bytes are equal
    if(cmp==0){
        // AND they have the same length
        if(a->str.len == b->str.len) return 0;
        // AND `a` is shorter than `b`
        else if (a->str.len > b->str.len) return 1;
        else return -1;
    }else{
        if(cmp<0) return -1;
        else return 1;
    }
}

/*================================== List object =============================*/

/* Initializes an empty list `tfobj`.*/
tfobj *createListObject(void){
    tfobj *o = createObject(TFOBJ_TYPE_LIST);
    o->list.ele = NULL;
    o->list.len = 0;
    return  o;
}

/* Append an element `ele` to the given list `l`.
 * This function doesn't increase the refcount of the element added to the list.*/
void listPush(tfobj *l, tfobj *ele){
    /* A new memory allocation is performed, with a dimension equal to the actual
     * size plus one (to have space for the new element). Note: sizeof(tfobj *)
     * is used because 'ele' is an array of pointers to tfobj.*/
    l->list.ele = xrealloc(l->list.ele, sizeof(tfobj*)*(l->list.len+1));

    l->list.ele[l->list.len] = ele;     // Append the element
    l->list.len++;                      // Update the list length
}


/*======================= Turn program into toy forth list ===================*/

/* Skip white spaces in the parser. */
void parserSpaces(tfparser *parser){
    while (isspace(parser->p[0])) parser->p++;
}

/* Given the parser stack position, return a number tfobj. */
#define MAX_NUM_LEN 128
tfobj *parseNumber(tfparser *parser){
    char *start = parser->p;    // Save the initial position.
    char *end;

    // Skip a possible minus at the beginning.
    if(parser->p[0] == '-') parser->p++;
    // Move to the end of the number.
    while(parser->p[0] && isdigit(parser->p[0])) parser->p++;
    end = parser->p;            // This is the first NON-digit character.

    int numlen = end-start;
    if(numlen>=MAX_NUM_LEN) return  NULL;

    char buf[MAX_NUM_LEN];      // Init a buffer for the number.
    memcpy(buf,start,numlen);
    buf[numlen] = 0;

    /* The atoi() function converts the initial  portion  of  the  string
       pointed to by nptr to int*/
    tfobj *o = createIntObject(atoi(buf));
    return  o;
}

/* Return true if the character is a valid symbol.*/
int is_symbol_char(int c){
    char symchars[] = "+-*/%";

    if(isalpha(c)) return 1;
    /* The  strchr() function returns a pointer to the first occurrence of the
     * character c in the string s.
     * If the function doesn't return NULL, means that c appears in symchars.*/
    else if(strchr(symchars,c)!=NULL) return 1;
    else return 0;

    // A compact version of the previous code
    // return isalpha(c) || strchr(symchars, c)!=NULL;
}

tfobj *parseSymbol(tfparser *parser){
    char *start = parser->p;    // Save the initial position.
    while(parser->p[0] && is_symbol_char(parser->p[0])) parser->p++;
    int symlen = parser->p - start;
    return createSymbolObject(start, symlen);
}

tfobj *compile(char *prg){
    tfparser parser;
    parser.prg = prg;
    parser.p = prg;

    tfobj *parsed = createListObject(); // Init blank list to return

    while(parser.p){

        tfobj *o;                       // Init a new tf object.
        char *token_start = parser.p;   // Save starting token position.

        parserSpaces(&parser);      // Skip white spaces.
        if(parser.p[0]==0) break;   // End of program.

        // Handle numbers.
        if(isdigit(parser.p[0]) || (parser.p[0]=='-' && isdigit(parser.p[1])) ){
            o = parseNumber(&parser);
        }
        // Handle symbols.
        else if(is_symbol_char(parser.p[0])){
            o = parseSymbol(&parser);
        }
        // Handle not valid characters
        else{
            o = NULL;
        }

        if(o==NULL){    // Display syntax error.
            release(parsed);
            printf("Syntax error near: %32s ...\n", token_start);
            return  NULL;
        } else{     // Append the new tfobj to the parsed list
            listPush(parsed, o);
        }
    }
    return parsed;
}

/*======================= Basic standard libraries ===========================*/

// Prototype functions used in basicMathFunction. (Currently unimplemented)

tfobj *ctxStackPop(tfctx *ctx, int tf_type);
int ctxCheckStackMinLen(tfctx *ctx, int ctx_len);
void ctxStackPush(tfctx *ctx, tfobj *tfobf);

void basicMathFunction(tfctx *ctx, tfobj *name){
    // NOTE: Requires implementation of stack manipulation functions (ctxStackPop, etc.)
    if(ctxCheckStackMinLen(ctx,2)) return;
    tfobj *b = ctxStackPop(ctx,TFOBJ_TYPE_INT);
    tfobj *a = ctxStackPop(ctx,TFOBJ_TYPE_INT);
    if(a==NULL || b==NULL) return;

    int result = 0;
    switch(name->str.ptr[0]) {
        case '+': result = a->i+b->i; break;
        case '-': result = a->i-b->i; break;
        case '*': result = a->i*b->i; break;
    };

    ctxStackPush(ctx, createIntObject(result));
}

/*======================== Execution and context =============================*/

/* Search for a function by name in the context's function table. */
tffuncentry *getFunctionByName(tfctx *ctx,tfobj *name){
    for(size_t j=0; j<ctx->functable.func_count; j++){
        tffuncentry *fe=ctx->functable.func_table[j];
        // Check if the function `name` already exists in the context
        if(compareStringObject(fe->name, name)==0){
            return fe;
        }
    }
    // Return NULL if the function `name` doesn't exist
    return NULL;
}

/* Add a new function entry to the context's function table. */
tffuncentry *registerFunction(tfctx *ctx, tfobj *name){
    // Dynamically reallocate memory for the new function table entry
    ctx->functable.func_table =
        xrealloc(ctx->functable.func_table,
                 sizeof(tffuncentry*)*(ctx->functable.func_count+1));
    tffuncentry *fe = xmalloc(sizeof(tffuncentry));

    // Add the new entry and increment the count
    ctx->functable.func_table[ctx->functable.func_count] = fe;
    ctx->functable.func_count++;

    // Initialize the function entry
    fe->name = name;
    // Retain the name object as the function table now holds a reference
    retain(name);
    fe->callback = NULL;
    fe->user_func = NULL;
    return fe;
}

/* Register a new C-implemented function given the `name` in the context `ctx`.
 * If a function with the same `name` already exists, its C implementation is overwritten. */
void registerCFunction(tfctx *ctx, char *name,
                       void (*callback) (tfctx *ctx, tfobj *name)){
    tffuncentry *fe;
    tfobj *oname = createStringObject(name, strlen(name));
    fe = getFunctionByName(ctx,oname);      // Check if `name` exists

    if(fe){
        // Existing function: overwrite C callback
        if(fe->user_func){
            // Release previous user-defined function if present
            release(fe->user_func);
            fe->user_func = NULL;
        }
        fe->callback = callback;
    }else{
        // New function: register it
        fe = registerFunction(ctx,oname);
        fe->callback = callback;
    }

    /* The oname object is either registered (retained) or discarded, so we
     * release the local copy. */
    release(oname);
}

tfctx *createContext(void){
    tfctx *ctx = xmalloc(sizeof(*ctx));
    ctx->stack = createListObject();
    ctx->functable.func_table = NULL;
    ctx->functable.func_count = 0;

    // registerCFunction(ctx, "+", basicMathFunction);
    return ctx;
}


/* Try to apply the function `fcn` to the context `ctx` stack.
 * Return 0 if the execution is properly solved and executed , 1 otherwise. */
// TODO: Needs full implementation to call fe->callback
int callSymbol(tfctx *ctx, tfobj *word){
    tffuncentry *fe = getFunctionByName(ctx,word);
    if(fe==NULL) return 1;
    return 0;
}

/* Execute the Toy Forth program stored in the list `prg`, using `ctx` context.*/
void exec(tfctx *ctx,tfobj *prg){
    /* If expression is  false  (i.e.,  compares equal  to zero), assert()
     * prints an error message to standard error and  terminates the program
     * by calling abort(3). */
    // Continue only if the tfobj is a list
    assert(prg->type == TFOBJ_TYPE_LIST);

    for(size_t j=0; j<prg->list.len; j++){
        tfobj *word = prg->list.ele[j];
        switch(word->type){
            case TFOBJ_TYPE_SYMBOL:
                callSymbol(ctx, word);
                break;
            default:
                // Add the symbol to the execution stack.
                listPush(ctx->stack, word);
                retain(word);
        }
    }
}
/*=================================== Main ===================================*/

int main(int argc, char **argv){
    /* By default the first element of argv is the program binary itself.
     * We expect to have 2 arguments: the toyforth compiler binary itself and
     * the toyforth code to compile.*/
    if (argc!=2){
        fprintf(stderr,"Usage: %s <filename>\n", argv[0]);
        return  1;
    }

    /* >>>> Read toyforth program from file <<< */
    // Open the toyforth file
    FILE *fp = fopen(argv[1],"r");
    if(fp==NULL){
        perror("Fail to open toyforth program");
        return 1;
    }
    /* The fseek() function sets the file position indicator for the stream
     * pointed to by stream. */
    // Go to the file position 0 starting from the end of the file.
    fseek(fp,0,SEEK_END);
    /* The  ftell() function obtains the current value of the file position
     * indicator for the stream pointed to by stream. */
    long file_size = ftell(fp);
    // printf("The file length is %ld\n", file_size);

    fseek(fp,0,SEEK_SET);                   // move to file start
    char *prgtext = xmalloc(file_size+1);   // memory allocation
    fread(prgtext,file_size,1,fp);          // read the program
    prgtext[file_size] = 0;                 // NULL terminator
    fclose(fp);

    printf("Program text: \"%s\"\n", prgtext);

    /* Given the program text, `compile` returns the `tfobj`.*/
    tfobj *prg = compile(prgtext);
    printObject(prg);
    printf("\n");

    tfctx *ctx = createContext();       // Init execution context
    exec(ctx, prg);

    printf("Context stack content:");
    printObject(ctx->stack);
    printf("\n");

    return  0;
}
