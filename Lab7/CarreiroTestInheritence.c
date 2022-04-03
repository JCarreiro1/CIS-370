#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
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
    int pid, fd, len;
    char text[50] = "";
    char temp[50] = "";

    fd = open("Part2Log.txt", O_WRONLY | O_CREAT, PERM);

    pid = fork();

    if(pid != 0){
        wait(NULL);
    }

    printList(argv);
    printList(envp);

    if(pid != 0){
        len = sprintf(text, "\n[p] this is process %d and my parent is %d", getpid(), getppid());
        write(fd, text, len);
        close(fd);
    } else{
        len = sprintf(text, "\t[c] this is process %d and my parent is %d", getpid(), getppid());
        write(fd, text, len);
    }

    return 0;
}