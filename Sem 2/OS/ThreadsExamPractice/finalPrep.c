#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
    int* l;
    int *il;
    int* u;
    int *iu;
    int *s;
    int n;
    pthread_mutex_t *mtxl, *mtxu, *mtxs;
    pthread_barrier_t *barrier;
} arg_t;

void* f(void* a){
    arg_t* arg = (arg_t*)a;
    pthread_barrier_wait(arg->barrier);
    int n = arg->n;
    while(n > 9){
        n /= 10;
    }
    if(n % 2 == 0){
        pthread_mutex_lock(arg->mtxu);;
        if(!*(arg->iu)){
            printf("I am the first one to write in u and I have the value %d\n", arg->n);
        }
        arg->u[(*(arg->iu))++] = arg->n;
        pthread_mutex_unlock(arg->mtxu);
    }else{
        pthread_mutex_lock(arg->mtxl);
        if(!*(arg->il)){
            printf("I am the first one to write in l and I have the value %d\n", arg->n);
        }
        arg->l[(*(arg->il))++] = arg->n;
        pthread_mutex_unlock(arg->mtxl);
    }
    pthread_mutex_lock(arg->mtxs);
    *arg->s += arg->n;
    pthread_mutex_unlock(arg->mtxs);

    return NULL;
}

int main(int, char**){
    int n;
    printf("Enter the number of elements:");
    scanf("%d", &n);
    int *arr = malloc(n * sizeof(int));
    printf("Enter the array: ");
    for(int i = 0; i < n; ++i){
        scanf("%d", &arr[i]);
    }

    arg_t* args = malloc(n * sizeof(arg_t));
    int* l = malloc(n * sizeof(int));
    int* u = malloc(n * sizeof(int));
    int *il = malloc(sizeof(int));
    *il = 0;
    int *iu = malloc(sizeof(int));
    *iu = 0;
    int *s = malloc(sizeof(int));
    *s = 0;
    pthread_mutex_t** mtxes = malloc(3 * sizeof(pthread_mutex_t*));
    for(int i = 0; i < 3; ++i){
        mtxes[i] = malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(mtxes[i], NULL);
    }
    pthread_barrier_t *barrier = malloc(sizeof(pthread_barrier_t));
    pthread_barrier_init(barrier, NULL, n);

    for(int i = 0; i < n; ++i){
        args[i].l = l;
        args[i].u = u;
        args[i].il = il;
        args[i].iu = iu;
        args[i].s = s;
        args[i].mtxl = mtxes[0];
        args[i].mtxu = mtxes[1];
        args[i].mtxs = mtxes[2];
        args[i].barrier = barrier;
        args[i].n = arr[i];
    }

    pthread_t* threads = malloc(n * sizeof(pthread_t));

    for(int i = 0; i < n; ++i){
        pthread_create(&threads[i], NULL, f, &args[i]);
    }

    for(int i = 0; i < n; ++i){
        pthread_join(threads[i], NULL);
    }

    printf("l has %d elements:", *il);
    for(int i = 0; i < *il; ++i){
        printf(" %d", l[i]);
    }
    printf("\n");
    printf("u has %d elements:", *iu);
    for(int i = 0; i < *iu; ++i){
        printf(" %d", u[i]);
    }
    printf("\n");
    printf("The sum of all the elements is %d\n", *s);

    free(threads);
    pthread_barrier_destroy(barrier);
    free(barrier);
    for(int i = 0; i < 3; ++i){
        pthread_mutex_destroy(mtxes[i]);
        free(mtxes[i]);
    }
    free(mtxes);
    free(s);
    free(iu);
    free(il);
    free(u);
    free(l);
    free(args);
    free(arr);

    return 0;
}
