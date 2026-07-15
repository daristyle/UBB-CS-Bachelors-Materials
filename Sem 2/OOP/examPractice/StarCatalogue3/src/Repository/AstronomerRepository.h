#pragma once

#include "Astronomer.h"
#include <vector>
using std::vector;

class AstronomerRepository {
private:
    string filename;
    vector<Astronomer> astronomers;

    void load();
public:
    AstronomerRepository(string filename);
    vector<Astronomer> getAstronomers();
};