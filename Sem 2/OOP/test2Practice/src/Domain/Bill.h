#pragma once

#include <string>

using std::string;

class Bill {
private:
    string company, serialNumber;
    double amount;
    bool paid;

public:
    Bill(string company, string serialNumber, double amount, bool paid);
    string getCompany() const;
    string getSerialNumber() const;
    double getAmount() const;
    bool isPaid() const;
};