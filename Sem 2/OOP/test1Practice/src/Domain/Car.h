#pragma once

#include <iostream>
#include <string>
using std::string, std::istream, std::ostream;

class Car{
private:
    string manufacturer;
    string model;
    int year;
    string color;
public:
    Car(string _manufacturer = "", string _model = "", int _year = 0, string _color = "");

    const string& getManufacturer() const;
    const string& getModel() const;
    int getYear() const;
    const string& getColor() const;

    bool operator==(const Car& car) const;

    friend ostream& operator<<(ostream& out,const Car& car);
};
