#include "AstronomerRepository.h"
#include <filesystem>
#include <fstream>

void AstronomerRepository::load(){
    std::ifstream fin{filename};
    string line;
    while(std::getline(fin, line)){
        string name, constellation;
        std::stringstream ss{line};
        getline(ss, name, '|');
        getline(ss, constellation);
        astronomers.push_back(Astronomer(name, constellation));
    }
}

AstronomerRepository::AstronomerRepository(string _filename): filename(_filename){
    if(!std::filesystem::exists(filename)){
        std::ofstream{filename};
    }
    load();
}

vector<Astronomer> AstronomerRepository::getAstronomers(){
    return astronomers;
}