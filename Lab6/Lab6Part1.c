#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **envp){
    int childStatus, parent = getpid();
    printf("%d *\n", getpid());
    fork();
    //wait(&childStatus);
    printf("%d **\n", getpid());
    fork();
    //wait(&childStatus);
    printf("%d ***\n", getpid());
    fork();
    //wait(&childStatus);
    printf("%d ****\n", getpid());
    fork();
    //wait(&childStatus);
    printf("%d *****\n", getpid());
    fork();
    printf("%d ******\n", getpid());
    //sleep(20);

    while(wait(&childStatus) != -1){
        
    }

    return EXIT_SUCCESS;
}