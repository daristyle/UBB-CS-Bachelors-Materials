#pragma once

#include <vector>
#include "../Domain/Car.h"
using std::vector;

class Repository{
private:
    vector<Car> cars;

public:
    Repository();

    void addCar(const Car& car);
    void removeCar(const Car& car);
    vector<Car> getCars() const;
};