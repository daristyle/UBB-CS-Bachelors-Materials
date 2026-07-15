#pragma once

#include "../Repository/Repository.h"

class Service {
private:
    Repository& repo;

public:
    Service(Repository& repo);

    vector<Bill> getBills();

    vector<Bill> getBillsSorted();

    double totalUnpaid(const string& company);
};