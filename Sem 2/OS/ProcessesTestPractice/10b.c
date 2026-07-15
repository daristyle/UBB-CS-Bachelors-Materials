#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>

int main(int, char**){
    if(mkfifo("10a2b", 0600) < 0 && errno != EEXIST){
        printf("mkfifo");
        exit(1);
    }
    if(mkfifo("10b2a", 0600) < 0 && errno != EEXIST){
        printf("mkfifo2");
        exit(1);
    }

    int a2b, b2a;
    a2b = open("10a2b", O_RDONLY);
    b2a = open("10b2a", O_WRONLY);

    int n;
    while(1){
        if(read(a2b, &n, sizeof(int)) <= 0) break;
        printf("B:%d\n", n);
        if(n < 5) break;
        n /= 2;
        if(write(b2a, &n, sizeof(int)) <= 0) break;
    }

    return 0;
}
