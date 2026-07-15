#pragma once

#include <string>

using std::string;

class Flight {
private:
    int hour, minute;
    string type;
    string destination;
    int delay;

public:
    Flight(int hour, int minute, string type, string destination, int delay);
    int getHour() const;
    int getMinute() const;
    string getType() const;
    string getDestination() const;
    int getDelay() const;
};