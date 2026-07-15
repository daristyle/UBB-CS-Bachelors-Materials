#include "historyRepository.h"

#include <stdlib.h>

#include "medicineRepository.h"

void destroyMedicineRepositoryAdapted(void *elem){
    /*
     * Helper function that gets a void* and destroys the medicine at it
     */
    destroyMedicineRepository((medicineRepository*)elem);
}

historyRepository* createHistoryRepository(){
    /*
     * Returns a pointer to a historyRepository
     */
    historyRepository* h = malloc(sizeof(historyRepository));
    h->history = createVector(INITIAL_CAPACITY, &destroyMedicineRepositoryAdapted);
    h->stack_pointer = -1;
    return h;
}

int addToHistoryRepository(historyRepository* h, medicineRepository* repo){
    /*
     * Adds a copy of the medicineRepository repo to the historyRepository h
     * Returns 1 if successful and 0 otherwise
     */
    while(size(h->history) > h->stack_pointer + 1){
        popBack(h->history);
    }
    int res = pushBack(h->history, repo);
    h->stack_pointer = size(h->history) - 1;
    return res;
}

medicineRepository* undoOperationFromHistoryRepository(historyRepository *history){
    /*
     * Returns a pointer to the next medicineRepository that needs undo or NULL if there is nothing to undo
     */
    if(history->stack_pointer <= 0) return NULL;
    medicineRepository* repo = (medicineRepository*)getElement(history->history, --history->stack_pointer);
    return repo;
}

medicineRepository* redoOperationFromHistoryRepository(historyRepository *history){
    /*
     * Returns a pointer to the next medicineRepository that needs to redo or NULL uf there is nothing to redo
     */
    if(history->stack_pointer >= size(history->history) - 1) return NULL;
    medicineRepository* repo = (medicineRepository*)getElement(history->history, ++history->stack_pointer);
    return repo;
}

void destroyHistoryRepository(historyRepository *history){
    /*
     * Destroys a historyRepository
     */
    destroyVector(history->history);
    free(history);
}