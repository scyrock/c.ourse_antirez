#include <stdio.h>

void clear(void){
    /*
     * Parameters: void - function takes no parameters
     * Return type: void - function doesn't return any value
     *
     * The clear function cleans the terminal.
     */

    /*
     * To know which sequence is used by the terminal to clear it, use:
     * clear | hexdump -C
     * - clear: is the unix command to investigate
     * - |: allows to pass the output of clear as input of hexdump
     * - hexdump -C: transforms the input in hexadecimal canonical form
     * The terminal output shows: |.[H.[2J.[3J|
     */

    /*
     * In this case a simplified clear sequence is used.
     * \x1b is the hexadecimal value of the ESC sequence.
     * (This information can be accessed by the command: man ascii).
     * This tells the terminal that the following characters are not
     * to be printed, but have to be interpreted as special commands.
     *
     * In this specific case:
     * - \x1b[ - ensures that the following values are not printed,
     *           but interpreted as terminal commands.
     * - H - performs cursor homing. Moves the terminal cursor to position (1,1).
     */
    printf("\x1b[H");
    
    /*
     * The some results could be achieved by using the command fflush.
     */
    // fflush(stdout);

}

int main(void){
    /*
     * The main function follows the standard structure for a function:
     * Name - main
     * Parameters - void: no input are provided
     * Return - int: an integer value is returned
     *          By convention 0 indicates that the software
     *          terminated without errors
     */
    
    /*
     * In C all the statements must be separated by semicolons (;).
     * C does not take into account any indentation or spacing rule.
     *
     * All the following implementations are equivalent:
     */
    //clear();printf("Hello world\n");
    //  clear();        printf("Hello world\n");
    //clear();      printf("Hello world\n");

    
    /*
     * clear function call:
     * - doesn't require any input - the brackets are empty
     * - doesn't return any output - no variable is used to store the returned value
     */
    clear();

    /*
     * printf is a standard function. As all C functions, brackets are used to
     * provide the function parameters.
     */
    printf("Hello world\n");

    /*
     * printf doesn't print the string character by character, but accumulates
     * information in an internal buffer up to an interruption sequence,
     * (such as \n) is provided.
     *
     * In this specific case this means that the printf function, in one instance,
     * prints both the clear() output and the "Hello world" (e.g. "\x1b[H Hello world\n").
     *
     * For this reason the program runs properly: firstly the terminal is cleared,
     * and after the string is printed.
     */
    return 0; 
}
