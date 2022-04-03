#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>


#define SIZE 512

int readLine(const char *fileName, int pos){
    char buf[SIZE];
    char error[100] = "Error! Could not open file!\n";
    int fd, nread, i;

    fd = open(fileName, O_RDONLY);

    if(fd == -1){
        write(1, error, 100);
        return -1;
    }
    
    lseek(fd, pos, SEEK_SET);

    nread = read(fd, buf, SIZE);

    for(i = 0; i < SIZE; i++){
        if((int)buf[i] == 10){
            pos++;
            i++;
            break;
        }
        pos++;
    }

    write(1, buf, i);
    close(fd);

    return pos;
}

int main(int argc, char **argv){
    int position = 0;
    int lines;
    char error[100] = "Incorrect number of arguments. Should be 4\n";

    if(argc != 4 && argc > 1){
        write(1, error, 100);
    } else{
        lines = atoi(argv[2]);

        if(argc == 1){
            lines = 5;

            for (int i = 0; i < lines; i++){
                position = readLine("lines.txt", position);
                if(position == -1){
                    break;
                }
            }

            return 0;
        }

        for (int i = 0; i < lines; i++){
            position = readLine(argv[3], position);
            if(position == -1){
                break;
            }
        }
    }

    return 0;
}