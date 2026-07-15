#include <string.h>
#include <stdio.h>
#include "service.h"

#include <stdlib.h>

#include "../Domain/medicine.h"
#include "../Domain/operation.h"
#include "../Repository/medicineRepository.h"
#include "../Repository/operationRepository.h"

service* createService(){
    service* s = malloc(sizeof(service));
    if(s == NULL){
        printf("malloc failed in createService");
        return NULL;
    }

    s->medRepo = createMedicineRepository();
    if(s->medRepo == NULL){
        free(s);
        printf("malloc failed in createService -> medRepo");
        return NULL;
    }

    s->opRepo = createOperationRepository();
    if(s->opRepo == NULL){
        free(s->medRepo);
        free(s);
        printf("malloc failed in createService -> opRepo");
        return NULL;
    }

    s->historyRepo = createHistoryRepository();
    if(s->historyRepo == NULL){
        free(s->opRepo);
        free(s->medRepo);
        free(s);
        printf("malloc failed in createService -> historyRepo");
        return NULL;
    }

    medicine* hard_coded_meds[]={
        createMedicine("Paracetamol", 1, 2, 100),
        createMedicine("Paracetamol", 5, 10, 100),
        createMedicine("Paracetamol", 10, 20, 100),
        createMedicine("Paracetamol", 25, 50, 100),
        createMedicine("Paracetamol", 50, 100, 100),
        createMedicine("Nurofen", 1, 10, 100),
        createMedicine("Nurofen", 5, 50, 100),
        createMedicine("Nurofen", 10, 100, 100),
        createMedicine("Nurofen", 25, 250, 100),
        createMedicine("Nurofen", 50, 500, 100)
    };
    for(int i = 0; i < 10; i++){
        addMedicineToRepository(s->medRepo, hard_coded_meds[i]);
        destroyMedicine(hard_coded_meds[i]);
    }

    medicineRepository *repo = copyMedicineRepository(s->medRepo);
    addToHistoryRepository(s->historyRepo, repo);

    return s;
}

int addMedicine(service* service, medicine *med){
    int res =  addMedicineToRepository(service->medRepo, med);
    if(res){
        addToHistoryRepository(service->historyRepo, copyMedicineRepository(service->medRepo));

        medicine *reverse_med = createMedicine(med->name, med->concentration, med->price, -med->quantity);
        functionCall *undo = createFunctionCall(addMedicineToRepository, service->medRepo, reverse_med);
        functionCall *redo = createFunctionCall(addMedicineToRepository, service->medRepo, copyMedicine(med));
        addOperation(service->opRepo, createOperation(undo, redo));
    }

    return res;
}
int removeMedicine(service* service, medicine *med){
    int res = removeMedicineFromRepository(service->medRepo, med);
    if(res){
        addToHistoryRepository(service->historyRepo, copyMedicineRepository(service->medRepo));

        functionCall *undo = createFunctionCall(addMedicineToRepository, service->medRepo, copyMedicine(med));
        functionCall *redo = createFunctionCall(removeMedicineFromRepository, service->medRepo, copyMedicine(med));
        addOperation(service->opRepo, createOperation(undo, redo));
    }

    return res;
}

int updateMedicine(service* service, medicine *med){
    medicine *temp = findMedicineInRepository(service->medRepo, med);
    medicine *old_med = copyMedicine(temp);
    int res = updateMedicineInRepository(service->medRepo, med);
    if(res){
        addToHistoryRepository(service->historyRepo, copyMedicineRepository(service->medRepo));

        functionCall *undo = createFunctionCall(updateMedicineInRepository, service->medRepo, old_med);
        functionCall *redo = createFunctionCall(updateMedicineInRepository, service->medRepo, copyMedicine(med));
        addOperation(service->opRepo, createOperation(undo, redo));
    }else{
        destroyMedicine(old_med);
        destroyMedicine(temp);
    }

    return res;
}

vector* getMedicinesContaining(service *service, char *str){
    return getMedicinesContainingFromRepository(service->medRepo, str);
}

vector* getConcentratedMedicines(service *service, int concentration){
    return getConcentratedMedicinesFromRepository(service->medRepo, concentration);
}

vector* getShortSuppliedMedicines(service *service, int quantity){
    return getShortSuppliedMedicinesFromRepository(service->medRepo, quantity);
}

void sortMedicinesAscending(service *service, vector *v){
    sortVector(v, lessMedicine);
}

void sortMedicinesDescending(service *service, vector *v){
    sortVector(v, greaterMedicine);
}

int undoCommand(service *service){
    return undoOperationFromRepository(service->opRepo);
}

int redoCommand(service *service){
    return redoOperationFromRepository(service->opRepo);
}

int undoHistory(service *service){
    medicineRepository *repo = undoOperationFromHistoryRepository(service->historyRepo);
    if(repo != NULL){
        destroyMedicineRepository(service->medRepo);
        service->medRepo = copyMedicineRepository(repo);
        return 1;
    }
    return 0;
}

int redoHistory(service *service){
    medicineRepository *repo = redoOperationFromHistoryRepository(service->historyRepo);
    if(repo != NULL){
        destroyMedicineRepository(service->medRepo);
        service->medRepo = copyMedicineRepository(repo);
        return 1;
    }
    return 0;
}

int undo(service *service){
    return COMMAND_DESIGN_PATTERN ? undoCommand(service) : undoHistory(service);
}

int redo(service *service){
    return COMMAND_DESIGN_PATTERN ? redoCommand(service) : redoHistory(service);
}

void destroyService(service* service){
    destroyMedicineRepository(service->medRepo);
    destroyOperationRepository(service->opRepo);
    destroyHistoryRepository(service->historyRepo);
    free(service);
}