#include "CSVFileRepository.h"
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sstream>

CSVFileRepository::CSVFileRepository(string _filename): FileRepository(_filename){
    load();
}

void CSVFileRepository::save() const{
    std::ofstream fout{this->filename};
    for(const auto& tutorial : this->repo->getAll()){
        fout << tutorial.get_title() << ',' << tutorial.get_presenter() << ',' << tutorial.get_duration() << ','
             << tutorial.get_likes() << ',' << tutorial.get_url() << '\n';
    }
}

void CSVFileRepository::load(){
    this->repo->clear();
    std::ifstream fin{this->filename};
    string line;
    while(getline(fin, line)){
        if(line.empty()) continue;
        std::stringstream ss{line};
        string title, presenter, url, min, sec, likes;
        getline(ss, title, ',');
        getline(ss, presenter, ',');
        getline(ss, min, ':');
        getline(ss, sec, ',');
        getline(ss, likes, ',');
        getline(ss, url);
        this->repo->add(Tutorial{title, presenter, {stoi(min), stoi(sec)}, stoi(likes), url});
    }
}

void CSVFileRepository::open(){
    if(fork() == 0){
        execlp("libreoffice", "libreoffice", "--calc", this->filename.c_str(), NULL);
        exit(1);
    }
}