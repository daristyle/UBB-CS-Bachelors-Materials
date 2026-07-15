#include "Bill.h"

Bill::Bill(string _company, string _serialNumber, double _amount, bool _paid):company{_company}, serialNumber{_serialNumber}, amount{_amount}, paid{_paid}{}

string Bill::getCompany() const{
    return company;
}

string Bill::getSerialNumber() const{
    return serialNumber;
}

double Bill::getAmount() const{
    return amount;
}

bool Bill::isPaid() const{
    return paid;
}