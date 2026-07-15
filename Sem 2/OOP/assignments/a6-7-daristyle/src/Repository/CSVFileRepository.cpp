#include "CSVFileRepository.h"
#include <fstream>
#include <iostream>
#include <unistd.h>

CSVFileRepository::CSVFileRepository(string _filename): FileRepository(_filename){
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
}

void CSVFileRepository::open(){
    if(fork() == 0){
        execlp("libreoffice", "libreoffice", "--calc", this->filename.c_str(), NULL);
        exit(1);
    }
}