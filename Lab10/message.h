#define MAX_SIZE 128

struct message {
    int new_data_flag; //either 0 or 1
    char text[MAX_SIZE];
};

int key = 789;
#define MSIZ = sizeof(struct message)