#pragma once

#include "../Domain/Car.h"
#include "../Repository/Repository.h"

class Service{
private:
    Repository repo;

public:
    Service(Repository _repo = Repository());

    void addCar(const Car& car);
    void removeCar(const Car& car);
    vector<Car> getCars() const;
    vector<Car> getVintageCars() const;
};