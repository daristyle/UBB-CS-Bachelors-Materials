#pragma once

#include "../Utilities/vector.h"
#include "../Domain/medicine.h"

typedef struct{
    vector* meds;
}medicineRepository;

medicineRepository* createMedicineRepository();
int addMedicineToRepository(medicineRepository *repo, medicine *med);
int removeMedicineFromRepository(medicineRepository *repo, medicine *med);
int updateMedicineInRepository(medicineRepository *repo, medicine *med);
medicine* findMedicineInRepository(medicineRepository *repo, medicine *med);
vector* getMedicinesContainingFromRepository(medicineRepository* repo, char *str);
vector* getConcentratedMedicinesFromRepository(medicineRepository* repo, int concentration);
vector* getShortSuppliedMedicinesFromRepository(medicineRepository* repo, int quantity);
void destroyMedicineRepository(medicineRepository* repo);
medicineRepository* copyMedicineRepository(medicineRepository* repo);