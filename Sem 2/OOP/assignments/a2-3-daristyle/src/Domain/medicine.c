#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "medicine.h"

medicine* createMedicine(char *name, int concentration, int price, int quantity){
    /*
     * Returns a pointer to a medicine with the given name, concentration, price and quantity
     */
    medicine* med = malloc(sizeof(medicine));

    med->name = malloc(strlen(name) * sizeof(char));
    if(med->name == NULL){
        printf("malloc failed in createMedicine");
    }
    strcpy(med->name, name);

    med->concentration = concentration;
    med->price = price;
    med->quantity = quantity;

    return med;
}

medicine* copyMedicine(medicine* med){
    /*
     *  Returns a pointer to a copy of the given medicine
     */
    return createMedicine(med->name, med->concentration, med->price, med->quantity);
}

char* getName(medicine* med){
    return med->name;
}

int getConcentration(medicine* med){
    return med->concentration;
}

int getPrice(medicine* med){
    return med->price;
}

int getQuantity(medicine* med){
    return med->quantity;
}

void setQuantity(medicine* med, int quantity){
    med->quantity = quantity;
}

void setPrice(medicine* med, int price){
    med->price = price;
}

void setConcentration(medicine* med, int concentration){
    med->concentration = concentration;
}

void setName(medicine* med, char *name){
    free(med->name);
    med->name = malloc(strlen(name) * sizeof(char));
    strcpy(med->name, name);
}

int lessMedicine(void* med1, void* med2){
    /*
     *  Returns -1 if med1 < med2, 1 if med1 > med2 and 0 if med1==med2
     */
    int nameCompare = strcmp(((medicine*)med1)->name, ((medicine*)med2)->name);
    if(nameCompare < 0){
        return -1;
    }else if(nameCompare > 0){
        return 1;
    }

    if(((medicine*)med1)->concentration < ((medicine*)med2)->concentration){
        return -1;
    }else if(((medicine*)med1)->concentration > ((medicine*)med2)->concentration){
        return 1;
    }

    if(((medicine*)med1)->quantity < ((medicine*)med2)->quantity){
        return -1;
    }else if(((medicine*)med1)->quantity > ((medicine*)med2)->quantity){
        return 1;
    }

    if(((medicine*)med1)->price < ((medicine*)med2)->price){
        return -1;
    }else if(((medicine*)med1)->price > ((medicine*)med2)->price){
        return 1;
    }

    return 0;
}

int greaterMedicine(void* med1, void* med2){
    /*
     *  Returns 1 if med1 < med2, -1 if med1 > med2 and 0 if med1==med2
     */
    return -lessMedicine(med1, med2);
}

char* intToString(int num){
    /*
     *  Returns a pointer to a string containing the digits of num
     *  Undefined if num < 0
     */
    int len = snprintf(NULL, 0, "%d", num);
    char* str = malloc(len + 1);
    if(str == NULL){
        printf("malloc failed in intToString");
        return NULL;
    }
    snprintf(str, len + 1, "%d", num);
    return str;
}

char* medicineToString(medicine *med){
    /*
     * Returns a pointer to a string representing the given medicine
     * Format: name - concentration% - quantity buc. - price lei/buc.
     */
    char *concentration = intToString(med->concentration);
    char *quantity = intToString(med->quantity);
    char *price = intToString(med->price);
    char *name = med->name;
    char *res = malloc(strlen(concentration) + strlen(quantity) + strlen(price) + strlen(name) + 3 * 3 + 1 + 5 + 9 + 1);
    if(res == NULL){
        free(concentration);
        free(quantity);
        free(price);
        printf("malloc failed in medicineToString");
        return NULL;
    }
    sprintf(res, "%s - %s%% - %s buc. - %s lei/buc.", name, concentration, quantity, price);
    free(concentration);
    free(quantity);
    free(price);
    return res;
}

void destroyMedicine(medicine *med){
    /*
     * Deallocates a medicine
     */
    free(med->name);
    free(med);
}