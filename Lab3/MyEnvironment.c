#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define PERM 0644
#define SIZE 512

int main(int argc, char **argv, char **envp){
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, PERM);
    for (char **env = envp; *env != 0; env++){
        char *thisEnv = *env;
        printf("%s\n", thisEnv);
        write(fd, thisEnv, SIZE);
    }

    return 0;
}