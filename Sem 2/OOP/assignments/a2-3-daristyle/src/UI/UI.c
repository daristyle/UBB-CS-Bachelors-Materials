#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UI.h"
#include "../Domain/medicine.h"
#include "../Services/service.h"

UI* createUI(){
    UI* ui = malloc(sizeof(UI));
    if(ui == NULL){
        printf("malloc failed in createUI");
        return NULL;
    }
    ui->service = createService();
    if(ui->service == NULL){
        free(ui);
        printf("malloc failed in createUI -> service");
        return NULL;
    }
    return ui;

}

void destroyUI(UI* ui){
    destroyService(ui->service);
    free(ui);
}

void printMenu(){
    printf("\n");
    printf("Medicine Management System\n");
    printf("1. Add Medicine\n");
    printf("2. Remove Medicine\n");
    printf("3. Update Medicine\n");
    printf("4. Filter Medicines by Name\n");
    printf("5. Filter Medicines by Concentration\n");
    printf("6. Display Short Supply\n");
    printf("7. Undo\n");
    printf("8. Redo\n");
    printf("0. Exit\n");
}

char* readString(char* msg){
    printf("%s", msg);
    char *str = NULL;
    long len = 0;
    int read = getline(&str, &len, stdin);

    if(read == -1){
        free(str);
        return NULL;
    }else if(read > 0 && str[read - 1] == '\n'){
        str[read - 1] = '\0';
    }

    return str;
}

int readInt(char* msg){
    int ret = 0, valid = 0;
    char *s, *endptr;
    do{
        s = readString(msg);
        if(s == NULL){
            printf("Input aborted\n");
            return 0;
        }

        ret = strtol(s, &endptr, 10);

        if(*endptr != '\0' || strlen(s) <= 0){
            printf("Invalid input\n");
        }else{
            valid = 1;
        }
        free(s);
    }while(!valid);

    return ret;
}

int readOrder(){
    int order, valid = 0;
    do{
        order = readInt("Do you want to sort the array ascending or descending?(Enter 1 for ascending or -1 for descending):");
        if(abs(order) != 1){
            printf("Invalid choice\n");
        }else{
            valid = 1;
        }
    }while(!valid);
    return order;
}

medicine* readMedicineDetailed(){
    char* name = readString("Enter the name of the medicine(no spaces):");
    int concentration = readInt("Enter the concentration of the medicine:");
    int price = readInt("Enter the price of the medicine:");
    int quantity = readInt("Enter the quantity of the medicine:");
    medicine* med = createMedicine(name, concentration, price, quantity);

    free(name);

    return med;
}

medicine* readMedicineSimple(){
    char* name = readString("Enter the name of the medicine(no spaces):");
    int concentration = readInt("Enter the concentration of the medicine:");
    medicine* med = createMedicine(name, concentration, 0, 0);

    free(name);

    return med;
}

int addMedicineUI(UI *ui){
    medicine* med = readMedicineDetailed();
    int res = addMedicine(ui->service, med);
    destroyMedicine(med);
    return res;
}

int removeMedicineUI(UI *ui){
    medicine* med = readMedicineSimple();
    int res = removeMedicine(ui->service, med);
    destroyMedicine(med);
    return res;
}

int updateMedicineUI(UI *ui){
    medicine* med = readMedicineDetailed();
    int res = updateMedicine(ui->service, med);
    destroyMedicine(med);
    return res;
}
void printMedicines(UI *ui, vector *meds){
    if(meds->size == 0){
        printf("No medicines found\n");
        return;
    }
    printf("Medicines found:");
    for(int i = 0; i < size(meds); i++){
        printf("\n%d.", i + 1);
        char *str = medicineToString((medicine*)getElement(meds, i));
        puts(str);
        free(str);
    }
}

void run(UI* ui){
    int exited = 0, choice;
    while(!exited){
        printMenu();
        choice = readInt("Enter your choice: ");
        switch(choice){
        case 1:
            if(addMedicineUI(ui)){
                printf("Medicine added successfully\n");
            }else{
                printf("Medicine not added\n");
            }
            break;
        case 2:

            if(removeMedicineUI(ui)){
                printf("Medicine removed successfully\n");
            }else{
                printf("Medicine not removed\n");
            }
            break;
        case 3:
            if(updateMedicineUI(ui)){
                printf("Medicine updated successfully\n");
            }else{
                printf("Medicine not updated\n");
            }
            break;
        case 4:
        case 5:
        case 6:
            char *str;
            int concentration;
            int quantity;
            if(choice == 4){
                str = readString("The medicines should contain:");
            }else if(choice == 5){
                concentration = readInt("The minimum concentration of the medicines:");
            }else if(choice == 6){
                quantity = readInt("The maximum quantity of the medicines:");
            }
            int order = readOrder();
            vector *res;
            if(choice == 4){
                res = getMedicinesContaining(ui->service, str);
            }else if(choice == 5){
                res = getConcentratedMedicines(ui->service, concentration);
            }else if(choice == 6){
                res = getShortSuppliedMedicines(ui->service, quantity);
            }
            if(order == 1){
                sortMedicinesAscending(ui->service, res);
            }else{
                sortMedicinesDescending(ui->service, res);
            }
            printMedicines(ui, res);
            destroyVector(res);
            if(choice == 4){
                free(str);
            }
            break;
        case 7:
            if(undo(ui->service)){
                printf("Undone\n");
            }else{
                printf("Nothing to undo\n");
            }
            break;
        case 8:
            if(redo(ui->service)){
                printf("Redone\n");
            }else{
                printf("Nothing to redo\n");
            }
            break;
        case 0:
            exited = 1;
            printf("Bye bye!\n");
            break;
        default:
            printf("Invalid choice\n");
        }
    }
}