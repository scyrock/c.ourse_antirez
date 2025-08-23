#include <stdio.h>

int main(void){
    int a = 28657;
     
    if(a%2==0){
        printf("%d is not prime.\n",a);
        return 0;
    }
    else{
        for(int i=3; i*i<a; i+=2){
            if(a%i==0){           
                printf("%d is not prime.\n",a); 
                return 0;
            }
        }
    }
    
    printf("%d is prime.\n",a);
    return 0;
}
