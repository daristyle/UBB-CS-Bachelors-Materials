#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <ctype.h>

struct arg_t{
    int *digits;
    int *letters;
    int *special;
    char* s;
    pthread_mutex_t* mtx;
};

void* f(void* a){
    struct arg_t* arg = (struct arg_t*)a;
    char* s = arg->s;
    int digits = 0, letters = 0, special = 0, i = 0;
    while(s[i]){
        if(isdigit(s[i])){
            ++digits;
        }else if(isalpha(s[i])){
            ++letters;
        }else{
            ++special;
        }
        ++i;
    }

    pthread_mutex_lock(arg->mtx);
    *(arg->digits) += digits;
    *(arg->letters) += letters;
    *(arg->special) += special;
    pthread_mutex_unlock(arg->mtx);

    return NULL;
}

int main(int argc, char** argv){
    printf("%d\n", argc);
    int *digits = malloc(sizeof(int));
    int *letters = malloc(sizeof(int));
    int *special = malloc(sizeof(int));
    pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mtx, NULL);
    struct arg_t** args = malloc((argc - 1) * sizeof(struct arg_t*));
    pthread_t *threads = malloc((argc - 1) * sizeof(pthread_t));
    for(int i = 0; i < argc - 1; ++i){
        args[i] = malloc(sizeof(struct arg_t));
        args[i]->digits = digits;
        args[i]->letters = letters;
        args[i]->special = special;
        args[i]->mtx = mtx;
        args[i]->s = argv[i + 1];

        pthread_create(&threads[i], NULL, f, args[i]);
    }
    for(int i = 0; i < argc - 1; ++i){
        pthread_join(threads[i], NULL);
        free(args[i]);
    }
    pthread_mutex_destroy(mtx);

    printf("Letters: %d\nDigits: %d\nSpecials: %d\n", *letters, *digits, *special);

    free(args);
    free(threads);
    free(mtx);
    free(digits);
    free(letters);
    free(special);

    return 0;
}
