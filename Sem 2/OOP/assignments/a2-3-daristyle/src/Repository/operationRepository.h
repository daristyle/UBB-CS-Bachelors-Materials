#pragma once
#include "vector.h"
#include "../Domain/operation.h"

typedef struct{
    vector *operations;
    int stack_pointer;
}operationRepository;

operationRepository* createOperationRepository();
int addOperation(operationRepository *repo, operation *op);
int undoOperationFromRepository(operationRepository *repo);
int redoOperationFromRepository(operationRepository *repo);
void destroyOperationRepository(operationRepository *repo);