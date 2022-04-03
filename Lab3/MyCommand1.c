#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    // argc starts at 1
    int *intArray;
    int sum = 0;

    intArray = (int *) malloc((argc) * sizeof(int));


    for (int i = 0; i < argc - 1; i++){
        intArray[i] = atoi(argv[i + 1]);
        printf("Array[%d] = %d\n", i, intArray[i]);
    }

    for (int i = 0; i < argc - 1; i++){
        sum += intArray[i];
    }

    if (argc == 1){
        printf("Please input a list of nonnegative integers\n");
    } else{
        printf("Sum = %d\n", sum);
    }
    
    free(intArray);

    return 0;
}