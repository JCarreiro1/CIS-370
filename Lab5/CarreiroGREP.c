#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#define SIZE 10000

/* Function takes in a character array that represents the file name that will be read.
   Takes a File and counts the number of new line characters within.
   Returns number of new line characters as the number of lines.
*/
int getFileLines(const char *fileName){
    int totLines = 0, fd, nread;
    char buf[SIZE];
    char error[100] = "Error! Could not open file!\n";

    // Open and read file into buffered array
    fd = open(fileName, O_RDONLY);

    if(fd == -1){
        write(1, error, 100);
        return -1;
    }

    nread = read(fd, buf, SIZE);

    // Increment through file and count number of new line characters
    for (int i = 0; i < nread; i++){
        if (buf[i] == 10){
            totLines ++;
        }
    }

    return totLines;
}

/* Function takes in character array that represents the file name, character array that represents the string to search for,
   And an integer that represents the current position in the file.
   This function searches a single line of a file to see if it contains the desired string. If so, the line is printed.
   Subsequent calls will search subsequent lines based on the updated position which is returned as an int.
*/
int grepLine(const char *fileName, const char *needle, int pos){
    char buf[SIZE] = "", line[SIZE] = "";
    char error[100] = "Error! Could not open file!\n";
    int fd, nread, i;

    fd = open(fileName, O_RDONLY);

    if(fd == -1){
        write(1, error, 100);
        return -1;
    }
    
    lseek(fd, pos, SEEK_SET);

    nread = read(fd, buf, SIZE);

    // Searches entire file (minus lines already searched from previous calls) until a new line character is encountered
    for(i = 0; i < SIZE; i++){
        if((int)buf[i] == 10){
            pos++;
            i++;
            break;
        }
        pos++;
    }

    // Populate new array just with the line to be searched
    for (int j = 0; j < i; j++){
        line[j] = buf[j];
    }

    // Write line if desired string is found
    if(strstr(line, needle)){
        write(1, buf, i);
    }

    close(fd);

    return pos;
}

int main(int argc, char **argv){
    int totalLines, position = 0;

    if(argc != 3){
        printf("Error! Incorrect number of arguments. Should be 3\n");
    } else{
        totalLines = getFileLines(argv[2]);

        for(int i = 0; i < totalLines; i++){
            position = grepLine(argv[2], argv[1], position);
        }
    }


    return 0;
}