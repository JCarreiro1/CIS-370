#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 128

int ForkExec(char *temp[]){
    if(fork()){
        wait(NULL);
    } else{
        execvp(temp[0], temp);
        exit(0);
    }

    return 0;
}

int main(void){
    char *input;
    char **args;
    int argNum = 0, curIndex = 0, argsize = 10, spaceNum = 0;

    //Infinite loop to coninually get user input
    while(1){
        input = malloc(MAX_LINE * sizeof(char));

        //prompt user and get input
        printf("myShell> ");
        fflush(stdout);

        fgets(input, MAX_LINE, stdin);

        //print for test purposes
        //printf("input: %s\n", input);

        spaceNum = 0;

        //find the number of actual arguments in the input for memory allocation
        for(int i = 0; i < MAX_LINE; i++){
            if(input[i] == 32){
                spaceNum++;
            }
        }

        //printf("numspaces: %d\n", spaceNum);

        //spaces will be 1 less than arguments, this fixes that
        spaceNum++;

        //printf("numspaces: %d\n", spaceNum);

        //allocate space for array of strings
        args = malloc(spaceNum * sizeof(char *));

        for(int i = 0; i < spaceNum; i++){
            args[i] = malloc(MAX_LINE * sizeof(char));
        }

        //Create a null terminated array of strings
        for(int i = 0; i < MAX_LINE; i++){
            //if current char is a space, go to next row of 2d array and set the end of the current row to NULL
            if(input[i] == 32){
                args[argNum][i] = '\0';
                argNum++;
                curIndex = 0;
                continue;
            }
            //if at the end of user input, set the rest of 2d array to NULL 
            else if(input[i] == 10){
                for(int j = argNum + 1; j < spaceNum; j++){
                    args[j][0] = 0;
                }

                break;
            }
            //copy arguments into array 
            else{
                args[argNum][curIndex] = input[i];
                curIndex++;
            }
        }

        //prints for testing purposes
        //printf("%s\n", args[0]);
        //printf("%s\n", args[1]);
        // printf("%s\n", args[2]);
        // printf("%s\n", args[3]);
        ForkExec(args);

        //Empty argument list (even though i free the memory anyways, getting rid of this breaks the program. I'll charge it rent)
        for(int i = 0; i < spaceNum; i++){
            args[i][0] = '\0';
        }


        //reset values for next iteration
        argNum = 0;
        curIndex = 0;
        spaceNum = 0;

        free(input);
        free(args);
    }
}