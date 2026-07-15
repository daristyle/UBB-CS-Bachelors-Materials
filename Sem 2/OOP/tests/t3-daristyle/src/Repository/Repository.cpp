#include "Repository.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

void Repository::trim(string& s){
    for(int i = 0; i < 2; i++){
        while(std::isblank(s.back())) s.pop_back();
        std::reverse(s.begin(), s.end());
    }
}

void Repository::load(){
    flights.clear();
    if(!std::filesystem::exists(this->filename)){
        std::ofstream{this->filename};
        std::cerr<<"File created!!";
    }
    std::ifstream fin{this->filename};
    string line;
    while(std::getline(fin, line)){
        string hour, minute, type, destination, delay;
        std::stringstream ss{line};
        getline(ss, hour, ';');
        getline(ss, minute, ';');
        getline(ss, type, ';');
        getline(ss, destination, ';');
        getline(ss, delay);
        trim(hour);
        trim(minute);
        trim(type);
        trim(destination);
        trim(delay);
        flights.push_back(Flight{stoi(hour), stoi(minute), type, destination, stoi(delay)});
    }
}

Repository::Repository(string _filename): filename(_filename){
    load();
}

vector<Flight> Repository::getFlights(){
    return this->flights;
}