#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main(int, char**){
    if(mkfifo("10a2b", 0600) < 0 && errno != EEXIST){
        printf("mkfifo1");
        exit(1);
    }
    if(mkfifo("10b2a", 0600) < 0 && errno != EEXIST){
        printf("mkfifo2");
        exit(1);
    }

    int a2b, b2a;
    a2b = open("10a2b", O_WRONLY);
    b2a = open("10b2a", O_RDONLY);

    srand(time(NULL));
    int n = rand() % 151 + 50;
    while(1){
        printf("A:%d\n", n);
        if(n < 5) break;
        n += n % 2;
        if(write(a2b, &n, sizeof(int)) <= 0) break;
        if(read(b2a, &n, sizeof(int)) <= 0) break;
    }

    return 0;
}
