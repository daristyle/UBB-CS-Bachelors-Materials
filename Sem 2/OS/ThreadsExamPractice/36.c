#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct arg_t{
    int id;
    int* potato;
    pthread_mutex_t* mtx;
};

void* f(void* a){
    struct arg_t* arg = (struct arg_t*)a;
    int* potato = arg->potato;
    pthread_mutex_t* mtx = arg->mtx;
    int exited = 0;
    while(!exited){
        int val = 10 + rand() % 91, time = 100 + rand() % 101;
        pthread_mutex_lock(mtx);
        if(*potato < 0){
             exited = 1;
        }else{
            *potato -= val;
            if(*potato < 0){
                printf("#%d reduced the potato to %d\n", arg->id, *potato);
                exited = 1;
            }
        }
        pthread_mutex_unlock(mtx);
        if(!exited){
            usleep(time * 1000);
        }
    }

    return NULL;
}

int main(int argc, char** argv){
    if(argc < 2){
        printf("Enter at least an argument");
        return 1;
    }
    srand(time(NULL));
    int n = atoi(argv[1]);
    int *potato = malloc(sizeof(int));
    *potato = 1000 + rand() % 9001;
    pthread_mutex_t* mtx = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mtx, NULL);
    struct arg_t **args = malloc(n * sizeof(struct arg_t*));
    pthread_t *threads = malloc(n * sizeof(pthread_t));
    for(int i = 0; i < n; ++i){
        args[i] = malloc(sizeof(struct arg_t));
        args[i]->id = i;
        args[i]->potato = potato;
        args[i]->mtx = mtx;
        pthread_create(&threads[i], NULL, f, args[i]);
    }

    for(int i = 0; i < n; ++i){
        pthread_join(threads[i], NULL);
        free(args[i]);
    }
    pthread_mutex_destroy(mtx);
    free(threads);
    free(args);
    free(mtx);
    free(potato);

    return 0;
}
