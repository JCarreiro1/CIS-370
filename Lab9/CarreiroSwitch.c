#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define PERM 0644

int main(int argc, char **argv){
    char outBuffer[128];
    char input;
    int fd, index = 1, curOut;

    fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, PERM);

    curOut = dup(1);

    while(1){
        sprintf(outBuffer, "Index %d\n", index);
        scanf(" %c", &input);

        if(input == '0'){
            break;
        } else if(input == 'f'){
            dup2(fd, 1);
        } else if(input == 's'){
            dup2(curOut, 1);
        }

        write(1, outBuffer, strlen(outBuffer));

        index++;
    }

    close(fd);

    return 0;
}