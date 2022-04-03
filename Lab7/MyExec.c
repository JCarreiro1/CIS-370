#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int printList(char **someList){
    int index = 0;

    while(someList[index] != NULL){
        printf("%s\n", someList[index]);
        index++;
    }

    return index;
}

int main(int argc, char **argv, char **envp){
    char text[50] = "";
    int fd;

    printf("Process ID In Exec: %d\n", getpid());
    printf("Parent Process ID In Exec: %d\n", getppid());

    fd = atoi(argv[1]);
    sprintf(text, "\n[c] this is process %d and my parent is %d", getpid(), getppid());
    write(fd, text, 47);

    printList(envp);

    exit(0);

    return 0;
}