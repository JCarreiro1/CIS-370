// When you run the program with the argumens "./progForkExec touch file.txt" a blank text documant called "file.txt" is created

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int ForkExec(char *temp[]){
    if(fork()){
        wait(NULL);
    } else{
        execvp(temp[0], temp);
        exit(0);
    }

    return 0;
}

int main(int argc, char **argv){
    ForkExec(argv + 1);
    write(1, "Done\n", 5);

    return 1;
}