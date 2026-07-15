#include "Service.h"
#include <algorithm>

Service::Service(Repository _repo): repo(_repo){}

void Service::addCar(const Car& car){
    this->repo.addCar(car);
}

void Service::removeCar(const Car& car){
    this->repo.removeCar(car);
}

vector<Car> Service::getCars() const{
    auto cars = this->repo.getCars();
    sort(cars.begin(), cars.end(), [](const Car& car1, const Car& car2){
        return car1.getManufacturer() != car2.getManufacturer() ? car1.getManufacturer() < car2.getManufacturer() : car1.getModel() < car2.getModel();
    });

    return cars;
}

vector<Car> Service::getVintageCars() const{
    auto cars = this->getCars();

    vector<Car> vintageCars;
    int maximumYear = 2026 - 45;
    std::copy_if(cars.begin(), cars.end(), std::back_inserter(vintageCars),
        [maximumYear](const Car& car){return car.getYear() <= maximumYear;});

    sort(vintageCars.begin(), vintageCars.end(), [](const Car& car1, const Car& car2){
        return car1.getColor() < car2.getColor();
    });

    return vintageCars;
}
