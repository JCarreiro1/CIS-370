#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define PERM 0644

int printList(char **someList){
    int index = 0;

    while(someList[index] != NULL){
        printf("%s\n", someList[index]);
        index++;
    }

    return index;
}

int main(int argc, char **argv, char **envp){
    int fd, check = 0;
    char text[50];
    char desc[10];

    printf("Process ID: %d\n", getpid());
    printf("Parent Process ID: %d\n", getppid());

    fd = open("ExecTest.txt", O_WRONLY | O_CREAT, PERM);

    sprintf(text, "\t[p] this is process %d and my parent is %d", getpid(), getppid());
    write(fd, text, 47);

    sprintf(desc, "%d", fd);

    //execlp("/home/mint/Lab7/progExec", *argv, desc, (char *) NULL);

    envp[1] = "Jonathan Carreiro";
    printList(envp);

    execle("/home/mint/Lab7/progExec", argv[0], desc, (char *) NULL, envp, (char *) NULL);

    close(fd);

    return 0;
}