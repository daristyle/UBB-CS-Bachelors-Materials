#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

#define READ 0
#define WRITE 1

int main(int, char**){
    int a2b[2], b2a[2];
    pipe(a2b);pipe(b2a);

    if(fork() == 0){
        close(a2b[READ]);close(b2a[WRITE]);
        srand(time(NULL));
        int x = rand() % 10 + 1;
        write(a2b[WRITE], &x, sizeof(int));
        printf("A: %d\n", x);
        while(1){
            read(b2a[READ], &x, sizeof(int));
            if(x == 10) break;
            x = rand() % 10 + 1;
            write(a2b[WRITE], &x, sizeof(int));
            printf("A: %d\n", x);
        }
        exit(0);
    }

    if(fork() == 0){
        close(b2a[READ]);close(a2b[WRITE]);
        srand(time(NULL));
        int x;
        while(1){
            read(a2b[READ], &x, sizeof(int));
            if(x == 10) break;
            x = rand() % 10 + 1;
            write(b2a[WRITE], &x, sizeof(int));
            printf("B: %d\n", x);
        }
        exit(0);
    }

    close(a2b[READ]);close(a2b[WRITE]);close(b2a[READ]);close(b2a[WRITE]);
    wait(0);wait(0);

    return 0;
}
