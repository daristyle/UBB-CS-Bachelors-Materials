#include "tests.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "../Domain/medicine.h"
#include "../Domain/operation.h"
#include "../Utilities/vector.h"
#include "../Repository/medicineRepository.h"
#include "../Repository/operationRepository.h"
#include "../Repository/historyRepository.h"
#include "../Services/service.h"

void testMedicine() {
    medicine* m = createMedicine("Aspenter", 100, 20, 50);
    assert(strcmp(getName(m), "Aspenter") == 0);
    assert(getConcentration(m) == 100);
    assert(getPrice(m) == 20);
    assert(getQuantity(m) == 50);

    setName(m, "Aspenter-Updated");
    assert(strcmp(getName(m), "Aspenter-Updated") == 0);
    setConcentration(m, 75);
    assert(getConcentration(m) == 75);
    setPrice(m, 25);
    assert(getPrice(m) == 25);
    setQuantity(m, 60);
    assert(getQuantity(m) == 60);

    medicine* copy = copyMedicine(m);
    assert(strcmp(getName(copy), "Aspenter-Updated") == 0);
    assert(getConcentration(copy) == 75);

    char* str = medicineToString(m);
    assert(strstr(str, "Aspenter-Updated") != NULL);
    free(str);

    assert(lessMedicine(m, copy) == 0);

    destroyMedicine(m);
    destroyMedicine(copy);
}

void testVector() {
    vector* v = createVector(2, free);
    int* e1 = malloc(sizeof(int)); *e1 = 1;
    int* e2 = malloc(sizeof(int)); *e2 = 2;
    int* e3 = malloc(sizeof(int)); *e3 = 3;

    pushBack(v, e1);
    pushBack(v, e2);
    pushBack(v, e3);
    assert(size(v) == 3);
    assert(*(int*)getElement(v, 0) == 1);

    int* e4 = malloc(sizeof(int)); *e4 = 4;
    setElement(v, 1, e4);
    assert(*(int*)getElement(v, 1) == 4);

    popBack(v);
    assert(size(v) == 2);

    destroyVector(v);
}


void testMedicineRepository() {
    medicineRepository* repo = createMedicineRepository();
    medicine* m1 = createMedicine("M1", 10, 10, 10);

    addMedicineToRepository(repo, m1);
    assert(size(repo->meds) == 1);

    medicine* m1_plus = createMedicine("M1", 10, 20, 5);
    addMedicineToRepository(repo, m1_plus);
    assert(size(repo->meds) == 1);
    medicine* found = findMedicineInRepository(repo, m1);
    assert(getQuantity(found) == 15);
    assert(getPrice(found) == 20);

    medicine* m2 = createMedicine("M2", 20, 20, 20);
    addMedicineToRepository(repo, m2);

    vector* filtered = getMedicinesContainingFromRepository(repo, "M");
    assert(size(filtered) == 2);
    destroyVector(filtered);

    removeMedicineFromRepository(repo, m1);
    assert(size(repo->meds) == 1);

    destroyMedicine(m1);
    destroyMedicine(m1_plus);
    destroyMedicine(m2);
    destroyMedicineRepository(repo);
}

void testService() {
    service* s = createService();
    int initialSize = size(s->medRepo->meds);

    medicine* m = createMedicine("TestMed", 100, 10, 10);
    addMedicine(s, m);
    assert(size(s->medRepo->meds) == initialSize + 1);

    undo(s);
    assert(size(s->medRepo->meds) == initialSize);

    redo(s);
    assert(size(s->medRepo->meds) == initialSize + 1);

    destroyMedicine(m);
    destroyService(s);
}

void testAll() {
    testMedicine();
    testVector();
    testMedicineRepository();
    testService();
}