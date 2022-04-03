#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(){
    int fd, childStatus;
    char p[7] = "parent\n";
    char c[6] = "child\n";

    fd = open("output.txt", O_WRONLY);

    if(fork()){
        write(fd, p, 7);
    } else{
        write(fd, c, 6);
    }
}