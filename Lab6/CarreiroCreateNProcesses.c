#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv){
    int n = atoi(argv[1]), parent = getpid(), childStatus;

    for (int i = 0; i < n; i++){
        if(getpid() == parent){
            if(!fork()){
                printf("\t[c] this is child process %d, my pid is %d\n", i + 1, getpid());
                sleep(2);
                return i + 1;
            }
        }
    }

    for(int i = 0; i < n; i++){
        if(getpid() == parent){
            int childpid = wait(&childStatus);
            printf("[p] child %d (pid = %d) just exited!\n", WEXITSTATUS(childStatus), childpid);
        } else{
            exit(0);
        }

    }

    printf("\nI am parent process (pid = %d) and all my child processes exited!\n", getpid());

    return 0;
}