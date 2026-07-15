#include "Repository.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

void Repository::trim(string& s){
    for(int i = 0; i < 2; i++){
        while(!s.empty() && isblank(s.back())) s.pop_back();
        std::reverse(s.begin(), s.end());
    }
}

void Repository::loadBills(){
    this->bills.clear();
    std::ifstream fin{this->filename};
    string line;
    while(getline(fin, line)){
        std::stringstream ss{line};
        string company, serialNumber, amount, paid;
        getline(ss, company, ';');
        getline(ss, serialNumber, ';');
        getline(ss, amount, ';');
        getline(ss, paid);
        trim(company);
        trim(serialNumber);
        trim(amount);
        trim(paid);
        bills.push_back(Bill{company, serialNumber, stod(amount), paid == "true"});
    }
}

Repository::Repository(string _filename): filename(_filename){
    if(!std::filesystem::exists(this->filename)){
        std::ofstream{this->filename};
    }
    loadBills();
}

vector<Bill> Repository::getBills(){
    return this->bills;
}