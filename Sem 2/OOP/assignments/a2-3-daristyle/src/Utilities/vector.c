#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "../Domain/medicine.h"
#include "../Domain/operation.h"

vector* createVector(int capacity, void (*destroy)(void*)){
    vector* v = malloc(sizeof(vector));
    if(v == NULL){
        printf("malloc failed in createVector -> v");
        return NULL;
    }
    v->elems = malloc(capacity * sizeof(void*));
    if(v->elems == NULL){
        free(v);
        printf("malloc failed in createVector -> elems");
        return NULL;
    }
    v->capacity = capacity;
    v->size = 0;
    v->destroy = destroy;
    return v;
}

int resizeVector(vector *v){
    if(v->size == v->capacity){
        void** temp = realloc(v->elems, v->capacity * 2 * sizeof(void*));
        if(temp == NULL){
            free(v -> elems);
            printf("realloc failed in resizeVector when increasing the size");
            return 0;
        }
        v->elems = temp;
        v->capacity *= 2;
    }else if(v->size < v->capacity / 4){
        int cap = v->capacity / 2;
        if(cap < 1){
            cap = 1;
        }
        void** temp = realloc(v->elems, cap * sizeof(void*));
        if(temp == NULL){
            free(v->elems);
            printf("realloc failed in resizeVector when decreasing the size");
            return 0;
        }
        v->elems = temp;
        v->capacity = cap;
    }
    return 1;
}

int pushBack(vector *v, void *elem){
    if(resizeVector(v)){
        v->elems[v->size++] = elem;
        return 1;
    }
    return 0;
}

int popBack(vector *v){
    if(v->size >= 1){
        v->destroy(v->elems[--v->size]);
    }
    return resizeVector(v);
}

int setElement(vector *v, int index, void *elem){
    if(index >= 0 && index < v->size){
        v->destroy(v->elems[index]);
        v->elems[index] = elem;
        return 1;
    }
    return 0;
}

void destroyVector(vector *v){
    for(int i = 0; i < v->size; i++){
        v->destroy(v->elems[i]);
    }
    free(v->elems);
    v->size = v->capacity = 0;
    free(v);
}

void sortVector(vector *v, int(*cmp)(void*, void*)){
    for(int i = 0; i < v->size - 1; i++){
        for(int j = i + 1; j < v->size; j++){
            if(cmp(v->elems[j], v->elems[i]) < 0){
                void* temp = v->elems[i];
                v->elems[i] = v->elems[j];
                v->elems[j] = temp;
            }
        }
    }
}

int size(vector* v){
    if(v == NULL){
        return -1;
    }
    return v->size;
}

void* getElement(vector* v, int index){
    if(v == NULL || index < 0 || index >= v->size){
        return NULL;
    }
    return v->elems[index];
}

vector* copyVector(vector* v){
    vector *w = malloc(sizeof(vector));
    if(w == NULL){
        printf("malloc failed in copyVector -> w");
        return NULL;
    }
    w->elems = malloc(v->capacity * sizeof(void*));
    if(w->elems == NULL){
        free(w);
        printf("malloc failed in copyVector -> elems");
        return NULL;
    }
    w->capacity = v->capacity;
    w->size = v->size;
    w->destroy = v->destroy;
    for(int i = 0; i < v->size; i++){
        w->elems[i] = v->elems[i];
    }
    return w;
}