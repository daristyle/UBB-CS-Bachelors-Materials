#include <string.h>
#include <stdlib.h>
#include "medicineRepository.h"

#include <stdio.h>

#include "../Utilities/vector.h"
#include "../Domain/medicine.h"

void destroyMedicineAdapted(void* elem){
    /*
     * Helper function that gets a void* and destroys the medicine at it
     */
    destroyMedicine((medicine*)elem);
}

void nothing(void* elem){
    /*
     * Helper function that gets a void* and does nothing
     */
}

medicineRepository* createMedicineRepository(){
    /*
     * Returns a pointer to a medicineRepository
     */
    medicineRepository* repo = malloc(sizeof(medicineRepository));
    if(repo == NULL){
        printf("malloc failed in createMedicineRepository");
        return NULL;
    }
    repo->meds = createVector(INITIAL_CAPACITY, &destroyMedicineAdapted);
    if(repo->meds == NULL){
        free(repo);
        printf("malloc failed in createMedicineRepository -> meds");
        return NULL;
    }
    return repo;
}

int searchMedicineInRepository(medicineRepository* repo, medicine *med){
    /*
     * Returns the index at which the medicine pointed at by med is found in the repository pointed at by repo or -1 if it is not there
     */
    int index = -1, i = 0;
    while(i < size(repo->meds) && index == -1){
        if(strcmp(getName((medicine*)getElement(repo->meds, i)), getName(med)) == 0 &&
          getConcentration((medicine*)getElement(repo->meds, i)) == getConcentration(med)){
            index = i;
          }
        ++i;
    }
    
    return index;
}

medicine* findMedicineInRepository(medicineRepository *repo, medicine *med){
    /*
     * Returns a pointer to a medicine in repo equal to that pointed at by med or an empty medicine if the medicine is not there
     */
    int index = searchMedicineInRepository(repo, med);
    if(index != -1){
        return (medicine*)getElement(repo->meds, index);
    }
    return createMedicine("", 0, 0, 0);
}

int addMedicineToRepository(medicineRepository* repo,medicine *med){
    /*
     * Adds the medicine pointed at by med to the repository pointed add by repo
     * Returns 1 if successful and 0 otherwise
     */
    int index = searchMedicineInRepository(repo, med);

    if(index == -1){
        return pushBack(repo->meds, copyMedicine(med));
    }
    medicine* elem = (medicine*)getElement(repo->meds, index);
    setQuantity(elem, getQuantity(elem) + getQuantity(med));
    setPrice(elem, getPrice(med));
    if(getQuantity((medicine*)getElement(repo->meds, index)) <= 0){
        removeMedicineFromRepository(repo, med);
    }
    return 1;
}

int removeMedicineFromRepository(medicineRepository* repo, medicine *med){
    /*
     * Removes the medicine equal to that pointed at by med from the repository pointed add by repo
     * Returns 1 if successful and 0 otherwise
     */
    int index = searchMedicineInRepository(repo, med);
    if(index != -1){
        setElement(repo->meds, index ,copyMedicine(getElement(repo->meds, size(repo->meds) - 1)));
        return popBack(repo->meds);
    }
    return 0;
}

int updateMedicineInRepository(medicineRepository* repo, medicine *med){
    /*
     * Updates the medicine pointed at by med in the repository pointed add by repo
     * Returns 1 if successful and 0 otherwise
     */
    int index = searchMedicineInRepository(repo, med);
    if(index != -1){
        setElement(repo->meds, index ,copyMedicine(med));
        return 1;
    }
    return 0;
}

vector* getMedicinesContainingFromRepository(medicineRepository *repo, char *str){
    /*
     * Returns a pointer to a vector that contains pointes to medicines in repo of the medciines that have str as a substring of their name
     */
    vector* res = createVector(INITIAL_CAPACITY, &nothing);

    for(int i = 0; i < size(repo->meds); i++){
        medicine* med = (medicine*)getElement(repo->meds, i);
        if(strcmp(str, "") == 0 || strstr(getName(med), str) != NULL){
            pushBack(res, med);
        }
    }

    return res;
}

vector* getConcentratedMedicinesFromRepository(medicineRepository* repo,  int concentration){
    vector* res = createVector(INITIAL_CAPACITY, &nothing);

    for(int i = 0; i < size(repo->meds); i++){
        medicine* med = (medicine*)getElement(repo->meds, i);
        if(getConcentration(med) >= concentration){
            pushBack(res, med);
        }
    }

    return res;
}

vector* getShortSuppliedMedicinesFromRepository(medicineRepository* repo, int quantity){
    vector* res = createVector(INITIAL_CAPACITY, &nothing);

    for(int i = 0; i < size(repo->meds); i++){
        medicine* med = (medicine*)getElement(repo->meds, i);
        if(getQuantity(med) <= quantity){
            pushBack(res, med);
        }
    }

    return res;
}

void destroyMedicineRepository(medicineRepository* repo){
    destroyVector(repo->meds);
    free(repo);
}

medicineRepository* copyMedicineRepository(medicineRepository* repo){
    medicineRepository* res = malloc(sizeof(medicineRepository));
    if(res == NULL){
        printf("malloc failed in copyMedicineRepository");
        return NULL;
    }
    res->meds = createVector(size(repo->meds), &destroyMedicineAdapted);
    if(res->meds == NULL){
        free(res);
        printf("malloc failed in copyMedicineRepository -> meds");
        return NULL;
    }
    for(int i = 0; i < size(repo->meds); i++){
        pushBack(res->meds, copyMedicine(getElement(repo->meds, i)));
    }
    return res;
}