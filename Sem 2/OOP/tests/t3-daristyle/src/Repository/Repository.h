#pragma once

#include "../Domain/Flight.h"

#include <vector>

using std::vector;

class Repository {
private:
    string filename;
    vector<Flight> flights;

    void trim(string& s);
    void load();
public:
    Repository(string filename);
    vector<Flight> getFlights();
};