#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

int main(int, char**){
    int a2b, b2a;

    a2b = open("7a2b", O_RDONLY);
    b2a = open("7b2a", O_WRONLY);

    srand(time(NULL));
    int x;
    while(1){
        read(a2b, &x, sizeof(int));
        if(x == 10) break;
        x = rand() % 10 + 1;
        write(b2a, &x, sizeof(int));
        printf("B: %d\n", x);
    }

    return 0;
}
