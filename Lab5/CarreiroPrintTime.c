#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#define SIZE 10000

int main(){
    char buf[SIZE];
    struct timeval start, end;
    double st, ed;

    for(int i = 0; i < SIZE; i++){
        buf[i] = 'a';
    }

    gettimeofday(&start, NULL);
    st = (double)start.tv_sec + ((double)start.tv_usec * 0.000001);

    //write(1, buf, SIZE);
    //printf("%s", buf);


    for(int i = 0; i < SIZE; i ++){
        write(1, buf, 1);
        //printf("%c", buf[i]);
    }

    gettimeofday(&end, NULL);
    ed = (double)end.tv_sec + ((double)end.tv_usec * 0.000001);

    printf("\nPrinting started at: %f", st);
    printf("\nPrinting ended at: %ld.%ld\n", end.tv_sec, end.tv_usec);
    printf("Printing took this long: %f\n", ed - st);

    return 0;
}