#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int **matrix;
int sum;
int rows, cols;
pthread_mutex_t mtx;

void* f(void* a){
    int row = (long)a;
    int suma = 0;
    for(int c = 0; c < cols; ++c){
        suma += matrix[row][c];
    }

    pthread_mutex_lock(&mtx);
    sum += suma;
    pthread_mutex_unlock(&mtx);

    return NULL;
}

int main(int, char**){
    FILE* fin = fopen("testMatrix.txt", "r");
    fscanf(fin, "%d %d", &rows, &cols);
    matrix = malloc(rows * sizeof(int*));
    for(int r = 0; r < rows; ++r){
        matrix[r] = malloc(cols * sizeof(int));
        for(int c = 0; c < cols; ++c){
            fscanf(fin, "%d", &matrix[r][c]);
        }
    }

    sum = 0;

    pthread_mutex_init(&mtx, NULL);

    pthread_t* threads = malloc(rows * sizeof(pthread_t));

    for(int r = 0; r < rows; ++r){
        pthread_create(&threads[r], NULL, f, (void*)(long)r);
    }

    for(int r = 0; r < rows; ++r){
        pthread_join(threads[r], NULL);
    }

    for(int r = 0; r < rows; ++r){
        free(matrix[r]);
    }
    free(matrix);
    free(threads);

    pthread_mutex_destroy(&mtx);

    printf("%d\n", sum);

    return 0;
}
