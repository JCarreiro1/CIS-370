#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv){
    int childStatus, parentPid, c1Status, c2Status, sum = 0, product = 1;

    parentPid = getpid();

    if(fork()){
        wait(&childStatus);
        c1Status = WEXITSTATUS(childStatus);
    } else{
        for(int i = 1; i < argc; i++){
            sum += atoi(argv[i]);
        }

        printf("Child 1 (pid: %d): sum = %d\n", getpid(), sum);

        if(sum >= 0){
            exit(0);
        } else{
            exit(1);
        }
    }

    if(fork()){
        wait(&childStatus);
        c2Status = WEXITSTATUS(childStatus);
    } else{
        for(int i = 1; i < argc; i++){
            product *= atoi(argv[i]);
        }

        printf("Child 2 (pid: %d): product = %d\n", getpid(), product);

        if(product >= 0){
            exit(0);
        } else{
            exit(1);
        }
    }

    if(c1Status){
        printf("Parent (pid: %d): sum was negative\n", parentPid);
    } else{
        printf("Parent (pid: %d): sum was nonnegative\n", parentPid);
    }

    if(c2Status){
        printf("Parent (pid: %d): product was negative\n", parentPid);
    } else{
        printf("Parent (pid: %d): product was nonnegative\n", parentPid);
    }

    return 0;
}