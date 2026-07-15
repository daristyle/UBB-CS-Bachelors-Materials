#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int* arr;
int n;
pthread_mutex_t mtx;
pthread_barrier_t barrier;

void* f(void *a){
    int pos = (long)a;
    arr[pos] = 10 + rand() % 11;
    pthread_barrier_wait(&barrier);
    while(1){
        pthread_mutex_lock(&mtx);
        if(arr[pos] <= 0){
            pthread_mutex_unlock(&mtx);
            break;
        }
        int finished = 1;
        for(int i = 0; i < n; ++i){
            if(i != pos){
                --arr[i];
                if(arr[i] > 0){
                    finished = 0;
                }
            }
        }

        pthread_mutex_unlock(&mtx);
        if(finished){
            break;
        }
    }

    return NULL;
}

int main(int, char**){
    srand(time(NULL));

    printf("Enter a number: ");
    scanf("%d", &n);

    pthread_t threads[n];
    arr = malloc(n * sizeof(int));
    pthread_mutex_init(&mtx, NULL);
    pthread_barrier_init(&barrier, NULL, n);
    for(int i = 0; i < n; ++i){
        pthread_create(&threads[i], NULL, f, (void*)(long)i);
    }

    for(int i = 0; i < n; ++i){
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mtx);
    pthread_barrier_destroy(&barrier);

    for(int i = 0; i < n; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);

    return 0;
}
