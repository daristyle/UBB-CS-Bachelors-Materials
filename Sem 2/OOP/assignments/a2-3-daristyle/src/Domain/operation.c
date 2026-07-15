#include "operation.h"

#include <stdlib.h>

functionCall* createFunctionCall(int (*func)(medicineRepository*, medicine*), medicineRepository *repo, medicine* med){
    /*
     * Returns a pointer to a functionCall
     */
    functionCall* fc = malloc(sizeof(functionCall));
    fc->func = func;
    fc->repo = repo;
    fc->med = med;
    return fc;
}

operation* createOperation(functionCall* undo, functionCall* redo){
    /*
     * Returns a pointer to an operation
     */
    operation* op = malloc(sizeof(operation));
    op->undo = undo;
    op->redo = redo;
    return op;
}

int callFunction(functionCall* fc){
    /*
     * Makes a functionCall
     */
    return fc->func(fc->repo, fc->med);
}

int undoOperation(operation *op){
    /*
     * Calls undo
     */
    return callFunction(op->undo);
}

int redoOperation(operation *op){
    /*
     * Calls redo
     */
    return callFunction(op->redo);
}

void destroyFunctionCall(functionCall* fc){
    /*
     * Deallocates a functionCall
     */
    destroyMedicine(fc->med);
    free(fc);
}

void destroyOperation(operation* op){
    /*
     * Deallocates an operation
     */
    destroyFunctionCall(op->undo);
    destroyFunctionCall(op->redo);
    free(op);
}