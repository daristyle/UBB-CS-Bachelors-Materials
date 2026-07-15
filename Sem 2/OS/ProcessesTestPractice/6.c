#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

#define READ 0
#define WRITE 1

int main(int argc, char** argv){
    if(argc != 2){
        printf("Insert one argument\n");
        exit(1);
    }

    int n = atoi(argv[1]);
    int p2c[2], c2p[2];

    pipe(p2c);pipe(c2p);

    if(fork() == 0){
        close(p2c[WRITE]);close(c2p[READ]);
        int sum = 0, x;
        for(int i = 0; i < n; ++i){
            read(p2c[READ], &x, sizeof(int));
            sum += x;
        }
        close(p2c[READ]);
        float avg = (float)sum / n;
        write(c2p[WRITE], &avg, sizeof(float));
        close(c2p[WRITE]);
        exit(0);
    }

    close(p2c[READ]);close(c2p[WRITE]);
    srand(time(NULL));
    for(int i = 0; i < n; ++i){
        int x = rand()%100;
        printf("%d " , x);
        write(p2c[WRITE], &x, sizeof(int));
    }
    close(p2c[WRITE]);

    float avg;
    read(c2p[READ], &avg, sizeof(float));
    close(c2p[READ]);

    printf("\n%f\n", avg);

    wait(0);

    return 0;
}
