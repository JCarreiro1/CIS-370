#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "buffer.h"

void consume(struct circBuff *ctrl){
    printf("%d consumed\n", ctrl->buffer[ctrl->out]);
    ctrl->buffer[ctrl->out] = NULL;
    ctrl->out = (ctrl->out + 1) % MAX_SIZE;
}

void printBuff(struct circBuff *ctrl){
    for(int i = 0; i < MAX_SIZE; i++){
        if(ctrl->buffer[(ctrl->out + i) % MAX_SIZE] != NULL){
            printf("%d ", ctrl->buffer[(ctrl->out + i) % MAX_SIZE]);
        }
    }

    printf("\n");
}

int main(){
    int id;
    struct circBuff *ctrl;
    char input;

    if( (id = shmget(key, sizeof(struct circBuff), 0 | 0666) ) < 0)
	{
		perror("Error: creating shared memory\n");
		exit(-1);
	}

    if( (ctrl = (struct circBuff *) shmat(id, 0, 0)) <= (struct circBuff *) (0) )
	{
		perror("Error: attaching shared memory\n");
		exit(-1);
	}

    ctrl->in = 0;
    ctrl->out = 0;
    for(int i = 0; i < MAX_SIZE; i++){
        ctrl->buffer[i] = NULL;
    }

    while(1){
        printf("Hit enter to consume from buffer or q to quit\n");
        scanf("%c", &input);

        if(input == 81 || input == 113){
            break;
        } else{
            if(ctrl->out == ctrl->in){
                printf("\t\t<Buffer is empty. Waiting for something to consume...>\n");
                while(ctrl->out == ctrl->in){
                    continue;
                }
            }

            consume(ctrl);
            printBuff(ctrl);
        }
    }

    //shmctl(id, IPC_RMID, 0);
    shmdt(ctrl);

    return 0;
}