#include <stdio.h>

int fact_calc(int num){
    if (num < 1){
        return 1;
    }
    return num*fact_calc(num-1);    
}

int main(void){
    unsigned int num = 5;
    unsigned int fact = fact_calc(num);
    printf("%d", fact);
}
