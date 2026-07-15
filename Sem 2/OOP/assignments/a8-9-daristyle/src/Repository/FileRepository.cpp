#include "FileRepository.h"
#include <fstream>
#include <filesystem>

FileRepository::FileRepository(string _filename): filename(_filename), repo(new MemoryRepository()){
    if(!std::filesystem::exists(_filename)){
        std::ofstream newFile{_filename};
        newFile.close();
    }
}

FileRepository::~FileRepository(){
    delete this->repo;
}

void FileRepository::load(){}
void FileRepository::save() const {}

void FileRepository::add(const Tutorial& tutorial){
    this->repo->add(tutorial);
    this->save();
}

void FileRepository::remove(const Tutorial& tutorial){
    this->repo->remove(tutorial);
    this->save();
}

void FileRepository::update(const Tutorial& tutorial){
    this->repo->update(tutorial);
    this->save();
}

int FileRepository::find(const Tutorial& tutorial) const{
    return this->repo->find(tutorial);
}

vector<Tutorial> FileRepository::getAll() const{
    return this->repo->getAll();
}

void FileRepository::likeTutorial(const Tutorial& tutorial){
    this->repo->likeTutorial(tutorial);
    this->save();
}

void FileRepository::clear(){
    this->repo->clear();
    this->save();
}