#pragma once

#include "src/Domain/Researcher.h"

#include <vector>
using std::vector;

class ResercherRepository{
private:
    vector<Researcher> researchers;
    string filename;

    void load();
public:
    ResercherRepository(string filename);
    vector<Researcher> getResearchers();
};