#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int value = 120;
    pid_t pid;
    pid = fork();

    if(pid < 0){
        perror("[error] fork() did not succeed");
        return -1;
    } else if(pid > 0){
        wait(NULL);
        value += 20;
        printf("A: value = %d\n", value);
        return 0;
    } else{
        value -= 20;
        printf("B: Value = %d\n", value);
        return 0;
    }
}