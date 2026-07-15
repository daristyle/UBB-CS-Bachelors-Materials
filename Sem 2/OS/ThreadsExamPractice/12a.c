#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int **matrix;
int *sums;
int rows, cols;

void* f(void* a){
    int row = (long)a;
    sums[row] = 0;
    for(int c = 0; c < cols; ++c){
        sums[row] += matrix[row][c];
    }

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

    sums = malloc(rows * sizeof(int));

    pthread_t* threads = malloc(rows * sizeof(pthread_t));

    for(int r = 0; r < rows; ++r){
        pthread_create(&threads[r], NULL, f, (void*)(long)r);
    }

    for(int r = 0; r < rows; ++r){
        pthread_join(threads[r], NULL);
    }

    for(int r = 0; r < rows; ++r){
        printf("%d\n", sums[r]);
        free(matrix[r]);
    }
    free(matrix);
    free(sums);
    free(threads);

    return 0;
}
