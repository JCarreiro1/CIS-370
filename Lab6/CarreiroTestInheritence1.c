#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    int n = 5, childStatus;

    if(fork()){
        printf("[p] n is: %d\n", n);
        wait(&childStatus);
        printf("[p] n is: %d\n", n);
    } else{
        sleep(5);
        printf("[c] n is: %d\n", n);
        n++;
        printf("[c] n is: %d\n", n);
    }
}