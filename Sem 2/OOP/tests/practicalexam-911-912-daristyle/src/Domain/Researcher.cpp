#include "Researcher.h"

Researcher::Researcher(string _name, string _position): name(_name), position(_position){
}

string Researcher::getName() const{
    return name;
}

string Researcher::getPosition() const{
    return position;
}