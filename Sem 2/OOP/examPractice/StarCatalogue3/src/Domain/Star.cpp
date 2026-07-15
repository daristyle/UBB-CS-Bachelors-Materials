#include "Star.h"

Star::Star(string _name, string _constellation, int _ra, int _dec, int _diam): name(_name), constellation(_constellation), ra(_ra), dec(_dec), diam(_diam){
}

string Star::getName() const{
    return name;
}

string Star::getConstellation() const{
    return constellation;
}

int Star::getRa() const{
    return ra;
}

int Star::getDec() const{
    return dec;
}

int Star::getDiam() const{
    return diam;
}