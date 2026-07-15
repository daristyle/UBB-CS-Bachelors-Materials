#include "Service.h"
#include <algorithm>
#include <stdexcept>

Service::Service(Repository& _repo): repo{_repo}{
}

vector<Bill> Service::getBills(){
    return repo.getBills();
}

vector<Bill> Service::getBillsSorted(){
    auto bills = getBills();
    std::sort(bills.begin(), bills.end(), [](Bill& a, Bill& b){return a.getCompany() < b.getCompany();});
    return bills;
}

double Service::totalUnpaid(const string& company){
    double sum = 0;
    bool found = false;
    for(const auto& bill : getBills()){
        if(bill.getCompany() == company){
            if(!bill.isPaid()){
                sum += bill.getAmount();
            }
            found = true;
        }
    }
    if(!found){
        throw std::runtime_error("Company not found");
    }
    return sum;
}