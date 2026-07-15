#include "StarRepository.h"
#include <filesystem>
#include <fstream>

void StarRepository::load(){
    std::ifstream fin{filename};
    string line;
    while(std::getline(fin, line)){
        string name, constellation, raString, decString, diamString;
        std::stringstream ss{line};
        getline(ss, name, '|');
        getline(ss, constellation, '|');
        getline(ss, raString, '|');
        getline(ss, decString, '|');
        getline(ss, diamString);
        int ra = std::stoi(raString);
        int dec = std::stoi(decString);
        int diam = std::stoi(diamString);
        stars.push_back(Star(name, constellation, ra, dec, diam));
    }
}

void StarRepository::save(){
    std::ofstream fout{filename};
    std::sort(stars.begin(), stars.end(), [](const Star& a, const Star& b){return a.getConstellation() < b.getConstellation();});
    for(auto star : stars){
        fout << star.getName() << "|" << star.getConstellation() << "|" << star.getRa() << "|" << star.getDec() << "|" << star.getDiam() << std::endl;
    }
}

StarRepository::StarRepository(string _filename): filename(_filename){
    if(!std::filesystem::exists(filename)){
        std::ofstream{filename};
    }
    load();
}

void StarRepository::addStar(Star star){
    stars.push_back(star);
}

vector<Star> StarRepository::getStars(){
    return stars;
}

StarRepository::~StarRepository(){
    save();
}
