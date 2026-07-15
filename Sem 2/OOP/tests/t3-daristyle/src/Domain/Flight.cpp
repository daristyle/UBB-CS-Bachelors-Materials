#include "Flight.h"

Flight::Flight(int _hour, int _minute, string _type, string _destination, int _delay):
                hour(_hour), minute(_minute), type(_type), destination(_destination), delay(_delay){
}

int Flight::getHour() const{
    return this->hour;
}

int Flight::getMinute() const{
    return this->minute;
}

string Flight::getType() const{
    return this->type;
}

string Flight::getDestination() const{
    return this->destination;
}

int Flight::getDelay() const{
    return this->delay;
}