#include "Repository.h"

#include <algorithm>
#include <stdexcept>

Repository::Repository(){
    this->cars.push_back(Car("Fiat", "Bravo", 2007, "red"));
    this->cars.push_back(Car("Fiat", "Idea", 2003, "black"));
    this->cars.push_back(Car("Audi", "A5", 2007, "blue"));
    this->cars.push_back(Car("BMW", "Coupe", 2013, "pink"));
    this->cars.push_back(Car("Ford", "Fiesta", 1976, "yellow"));
}

void Repository::addCar(const Car& car){
    auto it = std::find(this->cars.begin(), this->cars.end(), car);
    if(it != this->cars.end()){
        throw std::invalid_argument("Car already exists");
    }
    this->cars.push_back(car);
}

void Repository::removeCar(const Car& car){
    auto it = std::find(this->cars.begin(), this->cars.end(), car);
    if(it == this->cars.end()){
        throw std::invalid_argument("Car does not exist");
    }
    int pos = it - this->cars.begin();
    this->cars[pos] = this->cars.back();
    this->cars.pop_back();
}

vector<Car> Repository::getCars() const{
    return this->cars;
}