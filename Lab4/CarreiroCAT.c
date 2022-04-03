#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 512
#define PERM 0644

int copyFile(const char *name1, int outfile){
    int infile;
    ssize_t nread;
    char buffer[BUFSIZE];

    if((infile = open(name1, O_RDONLY)) == -1){
        return -1;
    }

    // if((outfile = open(name2, O_WRONLY|O_CREAT|O_TRUNC, PERM)) == -1){
    //     close(infile);
    //     return -2;
    // }

    while(nread = read(infile, buffer, BUFSIZE)){
        if(write(outfile, buffer, nread) < nread){
            close(infile);
            close(outfile);
            return -3;
        }
    }

    close(infile);
    //close(outfile);

    if(nread == -1){
        return -4;
    } else{
        return 0;
    }
}

int main(int argc, char **argv){
    char errMsg[100] = "Error! You should either use \"-s\" or \"-e\" then your file names.\n";
    char errMsg2[100] = "Error! Incorrect number of arguments. Should be 5\n";
    char buf[BUFSIZE];
    int fd, nread;

    if(argc != 5){
        write(1, errMsg2, 100);
    } else{
        fd = open(argv[4], O_WRONLY|O_CREAT|O_TRUNC, PERM);

        if (strcmp(argv[1], "-s") == 0){
            copyFile(argv[2], fd);
            copyFile(argv[3], fd);
            close(fd);

            fd = open(argv[4], O_RDONLY);
            while(nread = read(fd, buf, BUFSIZE)){
                write(1, buf, nread);
            }
        } else if (strcmp(argv[1], "-e") == 0){
            copyFile(argv[3], fd);
            copyFile(argv[2], fd);
            close(fd);

            fd = open(argv[4], O_RDONLY);
            while(nread = read(fd, buf, BUFSIZE)){
                write(1, buf, nread);
            }
        } else{
            write(1, errMsg, 100);
        }
    }



    return 0;
}