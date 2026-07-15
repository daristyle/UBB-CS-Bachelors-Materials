#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *arr;
int n;
pthread_cond_t print;
pthread_mutex_t mtx;

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

int isSorted(){
    int sorted = 1;
    for(int i = 1; i < n; ++i){
        if(arr[i] < arr[i - 1]){
            sorted = 0;
        }
    }
    return sorted;
}

void* sorter(void*){
    while(1){
        //printf("generator\n");
        pthread_mutex_lock(&mtx);
        if(isSorted()){
            pthread_cond_signal(&print);
            pthread_mutex_unlock(&mtx);
            break;
        }
        int i = rand() % n, j = rand() % n;
        if(j < i){
            swap(&i, &j);
        }
        if(arr[j] < arr[i]){
            swap(&arr[i], &arr[j]);
        }
        pthread_mutex_unlock(&mtx);
    }

    return NULL;
}

void* printer(void*){
    pthread_mutex_lock(&mtx);
    while(!isSorted()){
        pthread_cond_wait(&print, &mtx);
    }
    for(int i = 0; i < n; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n");
    pthread_mutex_unlock(&mtx);

    return NULL;
}

int main(int argc, char** argv){
    if(argc < 2){
        printf("Enter at least an arguments");
        return 1;
    }

    srand(time(NULL));

    sscanf(argv[1], "%d", &n);
    arr = malloc(n * sizeof(int));
    for(int i = 0; i < n; ++i){
        arr[i] = rand() % 1001;
    }

    pthread_t threads[n + 1];
    pthread_mutex_init(&mtx, NULL);
    pthread_cond_init(&print, NULL);
    for(int i = 0; i < n; ++i){
        pthread_create(&threads[i], NULL, sorter, NULL);
    }
    pthread_create(&threads[n], NULL, printer, NULL);
    for(int i = 0; i <= n; ++i){
        pthread_join(threads[i], NULL);
    }
    pthread_cond_destroy(&print);
    pthread_mutex_destroy(&mtx);
    free(arr);
    return 0;
}
