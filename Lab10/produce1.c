#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <time.h>
#include "buffer.h"

void produce(struct circBuff *ptr){
    int num;

    num = rand() % 100;
    ptr->buffer[ptr->in] = num;
    ptr->in = (ptr->in + 1) % MAX_SIZE;
    printf("%d was produced into buffer\n", num);
}

void printBuff(struct circBuff *ptr){
    for(int i = 0; i < MAX_SIZE; i++){
        if(ptr->buffer[(ptr->out + i) % MAX_SIZE] != NULL){
            printf("%d ", ptr->buffer[(ptr->out + i) % MAX_SIZE]);
        }
    }

    printf("\n");
}

int main(){
    int id;
    struct circBuff *ptr;
    char input;

    if( (id = shmget(key, sizeof(struct circBuff), IPC_CREAT | 0666) ) < 0)
	{
		perror("Error: creating shared memory\n");
		exit(-1);
	}

    if( (ptr = (struct circBuff *) shmat(id, 0, 0)) <= (struct circBuff *) (0) )
	{
		perror("Error: attaching shared memory\n");
		exit(-1);
	}

    ptr->in = 0;
    ptr->out = 0;
    for(int i = 0; i < MAX_SIZE; i++){
        ptr->buffer[i] = NULL;
    }

    srand(time(NULL));

    while(1){
        printf("Hit enter to produce to buffer or q to quit\n");
        scanf("%c", &input);

        if(input == 81 || input == 113){
            break;
        } else{
            if((ptr->in + 1) % MAX_SIZE == ptr->out){
                printf("\t\t\t<Buffer is full. Waiting for space...>\n");
                while((ptr->in + 1) % MAX_SIZE == ptr->out){
                    continue;
                }
            }

            produce(ptr);
            printBuff(ptr);
        }
    }

    return 0;
}