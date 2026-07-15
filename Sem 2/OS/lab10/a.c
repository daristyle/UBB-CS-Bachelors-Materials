#include <stdio.h>
#include <pthread.h>

void* f(void*){
    printf("f\n");
    return NULL;
}

int main(int, char**){
    pthread_t t;
    pthread_create(&t, NULL, f, NULL);
    printf("main\n");
    pthread_join(t, NULL);

    return 0;
}
