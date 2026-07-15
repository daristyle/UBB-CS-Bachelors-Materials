#pragma once

typedef struct{
    void **elems;
    int capacity;
    int size;
    void (*destroy)(void*);
}vector;

#define INITIAL_CAPACITY 1

vector* createVector(int capacity, void (*destroy)(void*));
int pushBack(vector *v, void *elem);
int popBack(vector *v);
int setElement(vector *v, int index, void *elem);
void destroyVector(vector *v);
void sortVector(vector *v, int(*cmp)(void*, void*));
int size(vector *v);
void* getElement(vector *v, int index);
vector* copyVector(vector *v);