#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <ctype.h>

void* f(void* a){
    int i = 0;
    char* s = (char*)a;
    while(s[i]){
        if(isupper(s[i])){
            s[i] += 'a' - 'A';
        }
        ++i;
    }

    return NULL;
}

int main(int argc, char** argv){
    pthread_t *threads = malloc((argc - 1) * sizeof(pthread_t));
    for(int i = 0; i < argc - 1; ++i){
        pthread_create(&threads[i], NULL, f, (void*)argv[i+1]);
    }

    for(int i = 0; i < argc - 1; ++i){
        pthread_join(threads[i], NULL);
    }

    for(int i = 1; i < argc; ++i){
        puts(argv[i]);
    }

    free(threads);

    return 0;
}
