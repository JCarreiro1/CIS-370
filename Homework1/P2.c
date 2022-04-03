#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t pid, pid1;
    
    pid = fork();

    if(pid > 0){
        wait(NULL);
        pid1 = getpid();
        printf("parent: pid = %d\n", pid); /* A */
        printf("parent: pid1 = %d\n", pid1); /* B */
    } else if(pid == 0){
        pid1 = getpid();
        printf("child: pid = %d\n", pid); /* C */
        printf("child: pid1 = %d\n", pid1); /* D */
    } else{
        fprintf(stderr, "Fork Failed");
        return 1;
    }

    return 0;
}