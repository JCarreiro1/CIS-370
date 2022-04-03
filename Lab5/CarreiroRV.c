#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 1024
#define PERM 0644

int fLength, totalLines;
bool flag = false;

/* Function takes in a character array that represents the file name that will be read.
   Takes a File and counts the number of new line characters within.
   Returns number of new line characters as the number of lines.
*/
int getFileLines(const char *fileName){
    int totLines = 0, fd, nread;
    char buf[SIZE];

    // Open and read file into buffered array
    fd = open(fileName, O_RDONLY);

    nread = read(fd, buf, SIZE);

    // Increment through file and count number of new line characters
    for (int i = 0; i < nread; i++){
        if (buf[i] == 10){
            totLines ++;
        }
    }

    return totLines;
}

/* Function takes in character array that represents the name of the file to be read,
   an integer that represents the file descriptor for the file to be written to,
   an integer that represents the current position in the file, and an integer that
   represents how many lines have been read in the file.
   Takes a file and reads the last line that has been unread and prints it.
   Returns an integer that updates the current position in the file.
*/
int readLastLine(const char *fileName, int outfile, int pos, int lines){
    // Sets two arrays to be empty so for the purpose of repeated function calls
    // temp will be holding the parts of the file yet to be printed
    // buf will be holding the part of the file that will be printed on this call
    char temp[SIZE] = "", buf[SIZE] = "";
    char error[100] = "Error! Could not open file!\n";
    int fd, i, nread, rread;

    fd = open(fileName, O_RDONLY);

    // Prints error if file cannot be opened
    if(fd == -1){
        write(1, error, 100);
        return -1;
    }
    
    // If reading for the first time, initialize the file length by reading entire file
    // Otherwise, read the entire file EXCLUDING lines already read while storing the remaining file length in nread
    if (lines == 0){
        fLength = read(fd, temp, SIZE);
        nread = fLength;
    } else{
        nread = read(fd, temp, (size_t) (fLength - pos));
    }

    // Loops through the unprinted part of the file, starting at the end, and checks for new line characters. The position in the file updates every iteration
    // i represents how much of the unprinted file is ok to print (i - nread = current line length). i must start at 2 less than nread for this to work
    for(i = nread - 2; i > 0; i--){
        // Once encountered, break from loop while still updating position in file
        if((int)temp[i] == 10){
            pos++;
            i++;
            break;
        }
        pos++;
    }

    // If this is the first  line of the file (final line to print) then undo the offset of -2
    if(lines == totalLines - 1){
        pos += 2;
    }

    // Set pointer to the end of the file and then move it back to the current position in the file.
    // Read file starting at updated position and ending at current line length
    lseek(fd, (off_t) - pos, SEEK_END);
    rread = read(fd, buf, nread - i);

    // If user used the flag to print to a file, redirect printing
    // Otherwise, print to console
    if(flag){
       write(outfile, buf, rread);
    } else{
        write(1, buf, pos);
    }

    close(fd);

    return pos;
}

int main(int argc, char **argv){
    int position = 0, linesRead, fd;
    char hints[3][30] = {
        {"[-]reverse -f <file1> <file2>"},
        {"[-]reverse <file1>"}
    };
    char error[100] = "Error! Could not open file!\n";

    // If the user enters the incorrect arguments, prints out hints on how to use command
    // Otherwise, run as normal
    if((strcmp(argv[1], "-f") == 0 && argc != 4) || (strcmp(argv[1], "-f") != 0 && argc != 2)){
        printf("%s\n%s\n", hints[0], hints[1]);
    } else{
        // If the flag is used, then adjust argv index, set flag to true, and open write file
        if(strcmp(argv[1], "-f") == 0){
            // Get amount of lines in file
            totalLines = getFileLines(argv[2]);
            flag = true;
            fd = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, PERM);

            // Prints error if file cannot be opened
            if(fd == -1){
                write(1, error, 100);
                return -1;
            }

            // Print each line in file in reverse order
            for(linesRead = 0; linesRead < totalLines; linesRead++){
                position = readLastLine(argv[2], fd, position, linesRead);
            }

            close(fd);
        } else{
            // Get amount of lines in file
            totalLines = getFileLines(argv[1]);

            // Print each line in file in reverse order
            for(linesRead = 0; linesRead < totalLines; linesRead++){
                position = readLastLine(argv[1], 0, position, linesRead);
            }
        }
    }


    return 0;
}