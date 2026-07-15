#include "operationRepository.h"

#include <stdlib.h>

#include "../Domain/operation.h"

void destroyOperationAdapted(void *elem){
    destroyOperation((operation*)elem);
}

operationRepository* createOperationRepository(){
    operationRepository* repo = malloc(sizeof(operationRepository));
    repo->operations = createVector(INITIAL_CAPACITY, &destroyOperationAdapted);
    repo->stack_pointer = -1;
    return repo;
}

int addOperation(operationRepository *repo, operation* op){
    while(size(repo->operations) > repo->stack_pointer + 1){
        popBack(repo->operations);
    }
    int res = pushBack(repo->operations, op);
    repo->stack_pointer = size(repo->operations) - 1;
    return res;
}

int undoOperationFromRepository(operationRepository *repo){
    if(repo->stack_pointer == -1) return 0;
    operation *op = (operation*)getElement(repo->operations, repo->stack_pointer--);
    return undoOperation(op);
}

int redoOperationFromRepository(operationRepository *repo){
    if(repo->stack_pointer >= size(repo->operations) - 1) return 0;
    operation *op = (operation*)getElement(repo->operations, ++repo->stack_pointer);
    return redoOperation(op);
}

void destroyOperationRepository(operationRepository *repo){
    destroyVector(repo->operations);
    free(repo);
}