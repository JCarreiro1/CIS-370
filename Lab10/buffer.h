#define MAX_SIZE 8

typedef struct circBuff {
    int in;
    int out;
    int buffer[MAX_SIZE];
} circBuff;

int key = 456;
#define MSIZ sizeof(struct circBuff)