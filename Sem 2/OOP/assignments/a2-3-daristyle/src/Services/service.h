#pragma once

#include "../Repository/medicineRepository.h"
#include "../Repository/operationRepository.h"
#include "../Repository/historyRepository.h"
#include "../Domain/medicine.h"

#define COMMAND_DESIGN_PATTERN 1

typedef struct{
    medicineRepository *medRepo;
    operationRepository *opRepo;
    historyRepository *historyRepo;
} service;

service* createService();
int addMedicine(service* service, medicine *med);
int removeMedicine(service* service, medicine *med);
int updateMedicine(service *service, medicine *med);
vector* getMedicinesContaining(service *service, char *str);
vector* getConcentratedMedicines(service *service, int concentration);
vector* getShortSuppliedMedicines(service *service, int quantity);
int undo(service* service);
int redo(service* service);
void sortMedicinesAscending(service* service, vector *v);
void sortMedicinesDescending(service *service, vector *v);
void destroyService(service* service);