#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

int main(int, char**){
    int a2b, b2a;

    a2b = open("7a2b", O_WRONLY);
    b2a = open("7b2a", O_RDONLY);

    srand(time(NULL));
    int x = rand() % 10 + 1;
    write(a2b, &x, sizeof(int));
    printf("A: %d\n", x);
    while(1){
        read(b2a, &x, sizeof(int));
        if(x == 10) break;
        x = rand() % 10 + 1;
        write(a2b, &x, sizeof(int));
        printf("A: %d\n", x);
    }

    return 0;
}
