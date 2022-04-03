#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    // argc starts at 1
    char **stringArray = NULL;

    stringArray = (char**) malloc((argc + 1) * sizeof(char*));

    for (int i = 0; i < argc; i++){
        stringArray[i] = (char*) malloc((strlen(argv[i]) + 1) * sizeof(char));
        strcpy(stringArray[i], argv[i]);
        printf("Array[%d]: %s\n", i, stringArray[i]);
    }

    free(stringArray);

    return 0;
}