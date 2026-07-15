#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

char s[129];
int m, idx = 0;
pthread_cond_t print, printed;
pthread_mutex_t mtx;

void* generator(void*){
    while(1){
        //printf("generator\n");
        pthread_mutex_lock(&mtx);
        if(m <= 0){
            pthread_cond_signal(&print);
            pthread_mutex_unlock(&mtx);
            break;
        }
        while(idx >= 128){
            pthread_cond_signal(&print);
            pthread_cond_wait(&printed, &mtx);
        }
        if(m <= 0){
            pthread_cond_signal(&print);
            pthread_mutex_unlock(&mtx);
            break;
        }
        s[idx++] = 'a' + rand() % 26;
        --m;
        pthread_mutex_unlock(&mtx);
    }

    return NULL;
}

void* printer(void*){
    while(1){
        //printf("printer\n");
        pthread_mutex_lock(&mtx);
        while(idx < 128 && m > 0){
            pthread_cond_wait(&print, &mtx);
        }
        s[idx] = '\0';
        printf("%s\n", s);
        idx = 0;
        pthread_cond_broadcast(&printed);
        if(m <= 0){
            pthread_mutex_unlock(&mtx);
            break;
        }
        pthread_mutex_unlock(&mtx);
    }

    return NULL;
}

int main(int argc, char** argv){
    if(argc < 3){
        printf("Enter at least 2 arguments");
        return 1;
    }

    srand(time(NULL));

    int n;
    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &m);

    pthread_t threads[n + 1];
    pthread_mutex_init(&mtx, NULL);
    pthread_cond_init(&print, NULL);
    pthread_cond_init(&printed, NULL);
    for(int i = 0; i < n; ++i){
        pthread_create(&threads[i], NULL, generator, NULL);
    }
    pthread_create(&threads[n], NULL, printer, NULL);
    for(int i = 0; i <= n; ++i){
        pthread_join(threads[i], NULL);
    }
    pthread_cond_destroy(&print);
    pthread_cond_destroy(&printed);
    pthread_mutex_destroy(&mtx);
    return 0;
}
