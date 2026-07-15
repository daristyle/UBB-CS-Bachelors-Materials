#pragma once

#include "medicineRepository.h"
#include "vector.h"

typedef struct{
    vector *history;
    int stack_pointer;
}historyRepository;

historyRepository* createHistoryRepository();
int addToHistoryRepository(historyRepository *h, medicineRepository *repo);
medicineRepository* undoOperationFromHistoryRepository(historyRepository *h);
medicineRepository* redoOperationFromHistoryRepository(historyRepository *h);
void destroyHistoryRepository(historyRepository *h);