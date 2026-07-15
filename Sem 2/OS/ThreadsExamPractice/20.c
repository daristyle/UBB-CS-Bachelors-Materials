#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int m;
pthread_mutex_t* mtx;
pthread_barrier_t barrier;

void* racer(void* a){
    pthread_barrier_wait(&barrier);
    for(int i = 0; i < m; ++i){
        pthread_mutex_lock(&mtx[i]);
        printf("%d entered checkpoint %d\n", (int)(long)a, i);
        usleep(100000 + rand() % 100001);
        pthread_mutex_unlock(&mtx[i]);
    }

    printf("%d finished\n", (int)(long)a);

    return NULL;
}

int main(int argc, char** argv){
    if(argc < 3){
        printf("Enter at least 2 arguments");
        return 1;
    }

    int n;
    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &m);

    pthread_t threads[n];
    mtx = malloc(m * sizeof(pthread_mutex_t));
    for(int i = 0; i < m; ++i){
        pthread_mutex_init(&mtx[i], NULL);
    }

    pthread_barrier_init(&barrier, NULL, n);
    for(int i = 0; i < n; ++i){
        pthread_create(&threads[i], NULL, racer, (void*)(long)i);
    }

    for(int i = 0; i < n; ++i){
        pthread_join(threads[i], NULL);
    }
    for(int i = 0; i < m; ++i){
        pthread_mutex_destroy(&mtx[i]);
    }
    free(mtx);
    pthread_barrier_destroy(&barrier);

    return 0;
}
