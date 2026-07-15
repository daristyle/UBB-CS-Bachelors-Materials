#pragma once

#include "Star.h"
#include <vector>
using std::vector;

class StarRepository {
private:
    string filename;
    vector<Star> stars;

    void load();
    void save();

public:
    StarRepository(string filename);
    vector<Star> getStars();
    void addStar(Star star);
    ~StarRepository();
};