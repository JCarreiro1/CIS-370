#include <stdio.h>
#include <string.h>

#define MAX_NUM_OF_ARGS 5
#define MAX_ARG_SIZE 256

int main(int argc, char **argv){
    // argc starts at 1
    char argumentArray[MAX_NUM_OF_ARGS][MAX_ARG_SIZE] = {
        {'d', 'e', 'f', 'a', 'u', 'l', 't', 'A', 'r', 'g'},
        {'d', 'e', 'f', 'a', 'u', 'l', 't', 'A', 'r', 'g'},
        {'d', 'e', 'f', 'a', 'u', 'l', 't', 'A', 'r', 'g'},
        {'d', 'e', 'f', 'a', 'u', 'l', 't', 'A', 'r', 'g'},
        {'d', 'e', 'f', 'a', 'u', 'l', 't', 'A', 'r', 'g'}
    };

    for (int i = 0; i < argc; i++){
        strcpy(argumentArray[i], argv[i]);
    }

    if (argc <= 5){
        for (int i = 0; i < MAX_NUM_OF_ARGS; i++){
            printf("Array[%d]: %s\n", i, argumentArray[i]);
        }
    } else{
        printf("You exceeded the maximum number of arguments (4)\n");
    }

    return 0;
}