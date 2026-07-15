#pragma once

#include <string>
using std::string;

class Star{
private:
    string name;
    string constellation;
    int ra;
    int dec;
    int diam;

public:
    Star(string name, string constellation, int ra, int dec, int diam);
    string getName() const;
    string getConstellation() const;
    int getRa() const;
    int getDec() const;
    int getDiam() const;
};
