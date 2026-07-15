#pragma once

#include <vector>
#include "../Domain/Bill.h"

using std::vector;

class Repository {
private:
    string filename;
    vector<Bill> bills;

    void loadBills();
    void trim(string& s);
public:
    Repository(string filename);
    vector<Bill> getBills();
};