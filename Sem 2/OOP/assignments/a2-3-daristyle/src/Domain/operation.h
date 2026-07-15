#pragma once

#include "medicine.h"
#include "../Repository/medicineRepository.h"//TODO is this oke??

typedef struct{
    int (*func)(medicineRepository*, medicine*);
    medicineRepository* repo;
    medicine* med;
}functionCall;

typedef struct{
    functionCall* undo;
    functionCall* redo;
}operation;

functionCall* createFunctionCall(int (*func)(medicineRepository *repo, medicine*), medicineRepository *repo, medicine* med);
operation* createOperation(functionCall* undo, functionCall* redo);
int undoOperation(operation *op);
int redoOperation(operation *op);
void destroyOperation(operation *op);