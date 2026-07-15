#include "ResercherRepository.h"
#include <fstream>
#include <sstream>
#include <filesystem>

void ResercherRepository::load(){
    std::ifstream fin{filename};
    string line, name, position;
    while(std::getline(fin, line)){
        std::stringstream ss{line};
        getline(ss, name, '|');
        getline(ss, position);
        researchers.push_back(Researcher(name, position));
    }
    fin.close();
}

ResercherRepository::ResercherRepository(string _filename): filename(_filename){
    if(!std::filesystem::exists(filename)){
        std::ofstream{filename}.close();
    }
    load();
}

vector<Researcher> ResercherRepository::getResearchers(){
    return researchers;
}