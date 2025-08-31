#include <stdio.h>

int main(void){
    // Init variables
    int arr_1[] = {1, 2, 0, 3, 4, 5};
    int size_int = sizeof(arr_1[0]);
    int size_arr = sizeof(arr_1);
    int len_arr = size_arr/size_int;

    // Compute the sum
    int sum = 0;
    for(int i=0; i<len_arr; i++){
        sum += arr_1[i];
    }
    
    // Print the result
    printf("Array: [");
    for(int i=0; i<len_arr-1; i++){
        printf("%d,", arr_1[i]);
    }

    printf("%d]\nSum of all elements: %d\n\n", arr_1[len_arr-1],sum);
    
    int arr_2[] = {10, -5, 3, 7};
    size_arr = sizeof(arr_2);
    len_arr = size_arr/size_int;

    sum = 0;
    for(int i=0; i<len_arr; i++){
        sum += arr_2[i];
    }

    printf("Array: [");
    for(int i=0; i<len_arr-1; i++){
        printf("%d,", arr_2[i]);
    }

    printf("%d]\nSum of all elements: %d\n\n", arr_1[len_arr-1],sum);
    return 0;
}
