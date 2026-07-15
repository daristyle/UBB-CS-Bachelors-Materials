#pragma once

typedef struct{
    int concentration;
    int price;
    int quantity;
    char *name;
}medicine;

char* getName(medicine* med);
int getConcentration(medicine* med);
int getPrice(medicine* med);
int getQuantity(medicine* med);
void setName(medicine* med, char *name);
void setConcentration(medicine* med, int concentration);
void setPrice(medicine* med, int price);
void setQuantity(medicine* med, int quantity);
medicine* createMedicine(char *name, int concentration, int price, int quantity);
medicine* copyMedicine(medicine *med);
char* medicineToString(medicine *med);
int lessMedicine(void* med1, void* med2);
int greaterMedicine(void* med1, void* med2);
void destroyMedicine(medicine *med);