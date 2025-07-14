#include <stdio.h>

int main(void){
    /*
     * In do-while the block is executed before checking the condition.
     */
    int i = 1;
    do{
        printf("%d\n",i);
        i++;
    }while(i<10);

    /*
     * The same implementation can be obtained by combining while with if and break.
     */
    i = 1;
    while(1){
        printf("%d\n",i);
        i++;
        if(i>=10) break;
    }

    return 0;
}
