#pragma once

#include "../Service/Service.h"

class UI{
private:
    Service service;

    void printMenu();
    void addCar();
    void removeCar();
    void printCars(string msg, vector<Car> cars);
    Car readCarDetailed();
    Car readCarSimplified();
public:
    UI(Service _service = Service());
    void run();
};