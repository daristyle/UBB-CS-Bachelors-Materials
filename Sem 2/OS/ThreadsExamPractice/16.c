#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <ctype.h>

struct arg_t{
    int* freq;
    char* s;
    pthread_mutex_t** mtx;
};

void* f(void* a){
    struct arg_t* arg = (struct arg_t*)a;
    char* s = arg->s;
    int fr[10];
    for(int i = 0; i < 10; ++i){
        fr[i] = 0;
    }
    int i = 0;
    while(s[i]){
        ++fr[s[i]-'0'];
        ++i;
    }

    for(i = 0; i < 10; ++i){
        if(fr[i]){
            pthread_mutex_lock(arg->mtx[i]);
            arg->freq[i] += fr[i];
            pthread_mutex_unlock(arg->mtx[i]);
        }
    }

    return NULL;
}

int main(int argc, char** argv){
    int* freq = malloc(10 * sizeof(int));
    for(int i = 0; i < 10; ++i){
        freq[i] = 0;
    }
    pthread_mutex_t** mtx = malloc(10 * sizeof(pthread_mutex_t*));
    for(int i = 0; i < 10; ++i){
        mtx[i] = malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(mtx[i], NULL);
    }
    struct arg_t** args = malloc((argc - 1) * sizeof(struct arg_t*));
    pthread_t *threads = malloc((argc - 1) * sizeof(pthread_t));
    for(int i = 0; i < argc - 1; ++i){
        args[i] = malloc(sizeof(struct arg_t));
        args[i]->freq = freq;
        args[i]->mtx = mtx;
        args[i]->s = argv[i + 1];

        pthread_create(&threads[i], NULL, f, args[i]);
    }
    for(int i = 0; i < argc - 1; ++i){
        pthread_join(threads[i], NULL);
        free(args[i]);
    }

    for(int i = 0; i < 10; ++i){
        pthread_mutex_destroy(mtx[i]);
        free(mtx[i]);
    }

    for(int i = 0; i < 10; ++i){
        printf("%d appears %d times\n", i, freq[i]);
    }

    free(args);
    free(threads);
    free(mtx);
    free(freq);

    return 0;
}
