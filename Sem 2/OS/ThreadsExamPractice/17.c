#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int *arr, size = 0, n;
pthread_mutex_t mtx;
pthread_cond_t evenPut, oddPut;

void* evenThread(void*){
    while(1){
        //printf("E%d\n", size);
        pthread_mutex_lock(&mtx);
        if(size >= n){
            pthread_mutex_unlock(&mtx);
            break;
        }
        while(size % 2 == 1){
            pthread_cond_wait(&oddPut, &mtx);
        }
        arr[size++] = rand() / 2 * 2;
        pthread_cond_signal(&evenPut);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

void* oddThread(void*){
    while(1){
        //printf("O%d\n", size);
        pthread_mutex_lock(&mtx);
        if(size >= n){
            pthread_mutex_unlock(&mtx);
            break;
        }
        while(size % 2 == 0){
            pthread_cond_wait(&evenPut, &mtx);
        }
        arr[size++] = rand() / 2 * 2 + 1;
        pthread_cond_signal(&oddPut);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main(int, char**){
    srand(time(NULL));
    printf("Enter a number: ");
    scanf("%d", &n);
    arr = malloc(n * sizeof(int));
    pthread_t oddthread, eventhread;
    pthread_mutex_init(&mtx, NULL);
    pthread_cond_init(&oddPut, NULL);
    pthread_cond_init(&evenPut, NULL);
    pthread_create(&eventhread, NULL, evenThread, NULL);
    pthread_create(&oddthread, NULL, oddThread, NULL);
    pthread_join(eventhread, NULL);
    pthread_join(oddthread, NULL);
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&evenPut);
    pthread_cond_destroy(&oddPut);

    for(int i = 0; i < n; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);

    return 0;
}
