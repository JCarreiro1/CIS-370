#include <unistd.h>

#define SIZE 512

char myToUpper(char input){
    if (input >= 97 && input <= 122){
        input -= 32;
    }

    return input;
}

int main(){
    int nread;
    char buf[SIZE];
    char temp[SIZE];

    while (nread = read(0, buf, SIZE)){
        for (int i = 0; i < SIZE; i++){
            buf[i] = myToUpper(buf[i]);
        }
        write(1, buf, nread);
    }

    return 0;
}