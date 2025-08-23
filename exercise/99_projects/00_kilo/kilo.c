/*** include ***/
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

/*** variables ***/
struct termios init_termios; // termios initial state

/*** terminal ***/

// handle errors
void die(const char *s){
    perror(s); // print errno varible
    exit(1);
}
void restoreRawMode(){
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &init_termios) == -1)
        die("tcsetattr");
}
// enable terminal raw mode
void enableRawMode(){
    // get the initial termios attributes
    if(tcgetattr(STDIN_FILENO, &init_termios) == -1)
        die("tcgetattr");
    // ensure that init condition is restored when kilo terminate
    atexit(restoreRawMode);
    
    struct termios raw = init_termios;
    // Bit flags values are flipped by &~
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON); 
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    // Define read() behaviour
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1; //read returns each 1/10 seconds

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

 /**main**/

int main(void){
    enableRawMode();

    // read the used input byte-by-byte and store it in c
    while(1){
        char c = '\0';
        if(read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
            die("read");
        if(iscntrl(c)) printf("%d\r\n", c);
        else printf("%d ('%c')\r\n", c,c);

        if(c=='q') break;
    }
    return 0; 
}
