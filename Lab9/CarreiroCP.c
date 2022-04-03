#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define PERM 0644
#define MAX_SIZE 512

int main(int argc, char **argv){
    int pipeFD[2], fd, nread;
    char buff[MAX_SIZE];

    if(argc != 3){
        printf("Incorrect number of arguments\n");
        exit(0);
    }

    pipe(pipeFD);

    if(fork()){
        close(pipeFD[0]);
        if((fd = open(argv[1], O_RDONLY, PERM) == -1){
            printf("Invalid file\n");
            exit(0);
        }
        nread = read(fd, buff, MAX_SIZE);
        write(pipeFD[1], buff, nread);
        wait(NULL);
    } else{
        close(pipeFD[1]);
        fd = open(argv[2], O_WRONLY | O_CREAT, PERM);
        nread = read(pipeFD[0], buff, MAX_SIZE);
        write(fd, buff, nread);
        close(pipeFD[0]);
        exit(0);
    }

    close(pipeFD[1]);

    return 0;
}