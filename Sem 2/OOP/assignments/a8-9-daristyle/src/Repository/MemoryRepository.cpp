#include "MemoryRepository.h"

#include <algorithm>
#include <iostream>
#include <ostream>

/*MemoryRepository::MemoryRepository(){
    this->tutorials.push_back({"C++", "Bejan", {10,4}, 100, "https://www.youtube.com/watch?v=dQw4w9WgXcQ"});
    this->tutorials.push_back({"C", "Bejan", {10,4}, 100, "https://www.youtube.com/watch?v=dQw4w9WgXcQ"});
    this->tutorials.push_back({"Java", "Bejan", {10,4}, 100, "https://www.youtube.com/watch?v=dQw4w9WgXcQ"});
    this->tutorials.push_back({"Python", "Bejan", {10,4}, 100, "https://www.youtube.com/watch?v=dQw4w9WgXcQ"});
    this->tutorials.push_back({"Assembly", "Bejan", {10,4}, 100, "https://www.youtube.com/watch?v=dQw4w9WgXcQ"});
    this->tutorials.push_back({"Go", "Bejan", {10,4}, 100, "https://www.youtube.com/watch?v=dQw4w9WgXcQ"});
    this->tutorials.push_back({"Ruby", "Bejan", {10,4}, 100, "https://www.youtube.com/watch?v=dQw4w9WgXcQ"});
    this->tutorials.push_back({"Javascript", "Bejan", {10,4}, 100, "https://www.youtube.com/watch?v=dQw4w9WgXcQ"});
    this->tutorials.push_back({"CSS", "Bejan", {10,4}, 100, "https://www.youtube.com/watch?v=dQw4w9WgXcQ"});
    this->tutorials.push_back({"HTML", "Bejan", {10,4}, 100, "https://www.youtube.com/watch?v=dQw4w9WgXcQ"});
}*/

int MemoryRepository::find(const Tutorial& tutorial) const{
    /*for(int i = 0; i < this->tutorials.size(); i++){
        if(this->tutorials[i] == tutorial)
            return i;
    }
    return -1;*/
    auto it = std::find(tutorials.begin(), tutorials.end(), tutorial);
    return it == tutorials.end() ? -1 : std::distance(tutorials.begin(), it);
}

void MemoryRepository::add(const Tutorial& tutorial){
    if(find(tutorial) != -1){
        throw RepositoryException("Tutorial already exists!");
    }
    this->tutorials.push_back(tutorial);
}

void MemoryRepository::remove(const Tutorial& tutorial){
    int pos = find(tutorial);
    if(pos == -1){
        throw RepositoryException("Tutorial not found!");
    }
    this->tutorials[pos] = this->tutorials.back();
    this->tutorials.pop_back();
}

void MemoryRepository::update(const Tutorial& tutorial){
    int pos = find(tutorial);
    if(pos == -1){
        throw RepositoryException("Tutorial not found!");
    }
    this->tutorials[pos] = tutorial;
}

vector<Tutorial> MemoryRepository::getAll() const{
    return this->tutorials;
}

void MemoryRepository::likeTutorial(const Tutorial& tutorial){
    auto pos = find(tutorial);
    if(pos != -1){
        this->tutorials[pos].like();
    }
}

void MemoryRepository::clear(){
    tutorials.clear();
}

void MemoryRepository::open(){
    std::cout << "MemoryRepository can't be opened!" << std::endl;
}
