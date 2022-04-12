#define MSGSIZE 128

typedef struct msgBuffer{
    long type;
    char message[MSGSIZE];
} msgBuffer;