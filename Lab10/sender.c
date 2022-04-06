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
    struct message *ptr;

    if( (id = shmget(key, sizeof(struct message), IPC_CREAT | 0666) ) < 0)
	{
		perror("Error: creating shared memory\n");
		exit(-1);
	}

    if( (ptr = (struct message *) shmat(id, 0, 0)) <= (struct message *) (0) )
	{
		perror("Error: attaching shared memory\n");
		exit(-1);
	}

    ptr->new_data_flag = 0;
    ptr->text[0] = '\0';

    while(1){
        printf("Enter a message (Enter \"quit\" to quit)\n");
        fgets(ptr->text, MAX_SIZE, stdin);

        ptr->new_data_flag = 1;

        if(strcmp(ptr->text, "quit\n") == 0){
            break;
        }

        while(ptr->new_data_flag == 1){
            continue;
        }
    }

    shmctl(id, IPC_RMID, 0);
    shmdt(ptr);

    return 0;
}