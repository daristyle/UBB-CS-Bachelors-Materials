#include "TextFileRepository.h"
#include <fstream>
#include <iostream>

TextFileRepository::TextFileRepository(string _filename): FileRepository(_filename){
    this->TextFileRepository::load();
}

void TextFileRepository::load(){
    std::ifstream fin{this->filename};
    Tutorial t;
    while(fin >> t){
        this->repo->add(t);
    }
    fin.close();
}

void TextFileRepository::save() const{
    std::ofstream fout{this->filename};
    for(const auto& t : this->repo->getAll()){
        fout << t << '\n';
    }
    fout << std::flush;
    fout.close();
}

void TextFileRepository::open(){
    std::cout << "TextFileRepository can't be opened!" << std::endl;
}
