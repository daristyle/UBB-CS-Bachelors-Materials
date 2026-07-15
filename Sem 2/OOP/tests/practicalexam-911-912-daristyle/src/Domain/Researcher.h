#pragma once

#include <string>
using std::string;

class Researcher {
private:
    string name;
    string position;

public:
    Researcher(string name, string position);
    string getName() const;
    string getPosition() const;
};