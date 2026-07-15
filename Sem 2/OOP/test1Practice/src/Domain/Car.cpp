#include "Car.h"

Car::Car(string _manufacturer, string _model, int _year, string _color):
    manufacturer(_manufacturer), model(_model), year(_year), color(_color){}

const string& Car::getManufacturer() const{
    return this->manufacturer;
}

const string& Car::getModel() const{
    return this->model;
}

int Car::getYear() const{
    return this->year;
}

const string& Car::getColor() const{
    return this->color;
}

bool Car::operator==(const Car& car) const{
    return this->manufacturer == car.manufacturer && this->model == car.model;
}

ostream& operator<<(ostream& out,const Car& car){
    out << car.manufacturer << " | " << car.model << " | " << car.year << " | " << car.color;
    return out;
}
