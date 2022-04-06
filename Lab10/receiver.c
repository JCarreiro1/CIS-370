#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include "message.h"

int main(){
    int id;
    struct message *ctrl;

    if( (id = shmget(key, sizeof(struct message), 0 | 0666) ) < 0)
	{
		perror("Error: creating shared memory\n");
		exit(-1);
	}

    if( (ctrl = (struct message *) shmat(id, 0, 0)) <= (struct message *) (0) )
	{
		perror("Error: attaching shared memory\n");
		exit(-1);
	}

    while(1){
        if(ctrl->new_data_flag == 0){
            printf("Waiting for message...\n");
            while(ctrl->new_data_flag == 0){
                continue;
            }
        }

        printf("Message received: %s\n", ctrl->text);
        ctrl->new_data_flag = 0;

        if(strcmp(ctrl->text, "quit\n") == 0){
            break;
        }
    }

    //shmctl(id, IPC_RMID, 0);
    shmdt(ctrl);

    return 0;
}