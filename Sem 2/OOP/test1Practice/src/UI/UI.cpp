#include "UI.h"
#include <iostream>
using std::cin, std::cout;

UI::UI(Service _service): service(_service){}

void UI::printMenu(){
    cout << "1. Add car\n"
         << "2. Remove car\n"
         << "3. Print all cars sorted by manufacturer and model\n"
         << "4. Print the vintage cars sorted by color\n"
         << "0. Exit\n"
         << std::flush;
}

Car UI::readCarDetailed(){
    string manufacturer, model, color, yearstr;
    cout << "Enter manufacturer: " << std::flush;
    cin >> manufacturer;
    cout << "Enter model: " << std::flush;
    cin >> model;
    cout << "Enter year: " << std::flush;
    cin >> yearstr;
    cout << "Enter color: " << std::flush;
    cin >> color;

    int year;
    try{
        year = std::stoi(yearstr);
    }catch(std::exception& e){
        throw std::invalid_argument("Invalid year");
    }

    return {manufacturer, model, year, color};
}

Car UI::readCarSimplified(){
    string manufacturer, model;
    cout << "Enter manufacturer: " << std::flush;
    cin >> manufacturer;
    cout << "Enter model: " << std::flush;
    cin >> model;

    return {manufacturer, model};
}

void UI::addCar(){
    this->service.addCar(this->readCarDetailed());
    cout << "Car added" << std::endl;
}

void UI::removeCar(){
    this->service.removeCar(this->readCarSimplified());
    cout << "Car removed" << std::endl;
}

void UI::printCars(string msg, vector<Car> cars){
    if(cars.empty()){
        cout << "No cars found" << std::endl;
        return;
    }
    cout << msg << '\n';
    for(const auto& car: cars){
        cout << car << '\n';
    }
    cout << std::flush;
}

void UI::run(){
    bool exited = false;
    while(!exited){
        this->printMenu();
        string choice;
        cout << "Enter your choice: ";
        cin >> choice;
        try{
            if(choice == "1"){
                this->addCar();
            }else if(choice == "2"){
                this->removeCar();
            }else if(choice == "3"){
                this->printCars("All the cars", this->service.getCars());
            }else if(choice == "4"){
                this->printCars("Vintage cars", this->service.getVintageCars());
            }else if(choice == "0"){
                exited = true;
                cout << "Bye bye!" << std::endl;
            }else{
                cout << "Invalid choice" << std::endl;
            }
        }catch(std::exception& e){
            cout << e.what() << std::endl;
        }
    }
}