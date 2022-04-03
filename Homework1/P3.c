#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFF_SIZE 8

struct circBuff{
    int in;
    int out;
    int buffer[BUFF_SIZE];
};

void produce(struct circBuff *cb){
    int num;

    num = rand() % 100;
    cb->buffer[cb->in] = num;
    cb->in = (cb->in + 1) % BUFF_SIZE;
    printf("%d was produced into buffer\n", num);
}

void consume(struct circBuff *cb){
    printf("%d consumed\n", cb->buffer[cb->out]);
    cb->buffer[cb->out] = NULL;
    cb->out = (cb->out + 1) % BUFF_SIZE;
}

void printBuff(struct circBuff *cb){
    for(int i = 0; i < BUFF_SIZE; i++){
        if(cb->buffer[(cb->out + i) % BUFF_SIZE] != NULL){
            printf("%d ", cb->buffer[(cb->out + i) % BUFF_SIZE]);
        }
    }

    printf("\n");
}

int main(){
    char input;
    struct circBuff cb;

    // Initialize circular buffer structure values
    cb.in = 0;
    cb.out = 0;
    for(int i = 0; i < BUFF_SIZE; i++){
        cb.buffer[i] = NULL;
    }

    srand(time(NULL));

    // Loops infinitely until user exits with 'q'
    while(1){
        printf("Enter p to produce to buffer, c to consume from buffer, or q to quit\n");
        scanf(" %c", &input);
        
        if(input == 81 || input == 113){
            break;
        }
        else if(input == 80 || input == 112){
            if((cb.in + 1) % BUFF_SIZE != cb.out){
                produce(&cb);
                printBuff(&cb);
            } else{
                printf("\t\t\t<Buffer is full>\n");
            }
            continue;
        }
        else if(input == 67 || input == 99){
            if(cb.out != cb.in){
                consume(&cb);
                printBuff(&cb);
            } else{
                printf("\t\t\t<Buffer is empty>\n");
            }
            continue;
        }
        else{
            printf("Invalid character\n");
        }
    }
    
    return 0;
}