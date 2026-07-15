#include "Astronomer.h"

Astronomer::Astronomer(string _name, string _constellation): name(_name), constellation(_constellation){
}

string Astronomer::getName() const{
    return name;
}

string Astronomer::getConstellation() const{
    return constellation;
}