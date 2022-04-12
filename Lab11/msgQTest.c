/* ANSWER TO PART 2:
   When using 0 in the msgrcv() function instead of IPC_NOWAIT,
   the function gets blocked and waits for a message to enter the queue.
   When using IPC_NOWAIT in the msgrcv() function,
   the function does not get blocked and the program continues to the print statement.
   The printed message is "(0): ". This is because the msgrcv() function doesn't get do read anything,
   resulting in a default value for the message type and an empty string for the message.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "message.h"

int main(int argc, char **argv){
    int msqID;
    key_t key;
    msgBuffer buffer;
    size_t buffLength;

    // Creating a message queue
    if(strcmp(argv[1], "-c/C") == 0){
        if(argc != 3){
            printf("[error] Command must be in the following form: ./progQ -c/C <key>\n");
            return -1;
        }

        key = atoi(argv[2]);

        if(msgget(key, IPC_CREAT | 0666) < 0){
            perror("[error] Could not create message queue!\n");
            exit(EXIT_FAILURE);
        }
    }

    // Sending a message to the queue
    if(strcmp(argv[1], "-s/S") == 0){
        if(argc != 5){
            printf("[error] Command must be in the following form: ./progQ -s/S <key> <type> <text>\n");
            return -2;
        }

        key = atoi(argv[2]);
        msqID = msgget(key, 0666);

        buffer.type = atoi(argv[3]);
        strncpy(buffer.message, argv[4], MSGSIZE);
        buffLength = strlen(buffer.message) + 1;
        msgsnd(msqID, &buffer, buffLength, IPC_NOWAIT);
    }

    // Read a message from the queue
    if(strcmp(argv[1], "-r/R") == 0){
        if(argc != 4){
            printf("[error] Command must be in the following form: ./progQ -r/R <key> <type>\n");
            return -3;
        }

        key = atoi(argv[2]);
        msqID = msgget(key, 0666);

        msgrcv(msqID, &buffer, MSGSIZE, atoi(argv[3]), IPC_NOWAIT);
        printf("(%ld): %s\n", buffer.type, buffer.message);
    }

    // Delete a message queue
    if(strcmp(argv[1], "-d/D") == 0){
        if(argc != 3){
            printf("[error] Command must be in the following form: ./progQ -d/D <key>\n");
            return -4;
        }

        key = atoi(argv[2]);
        msqID = msgget(key, 0666);

        msgctl(msqID, IPC_RMID, NULL);
    }

    return 0;
}