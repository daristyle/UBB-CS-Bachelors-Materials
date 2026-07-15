#pragma once

#include <string>
using std::string;

class Astronomer {
private:
    string name;
    string constellation;

public:
    Astronomer(string name, string constellation);
    string getName() const;
    string getConstellation() const;
};