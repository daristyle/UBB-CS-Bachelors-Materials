#include "Idea.h"
#include <fstream>

Idea::Idea(string title, string description, string status, string creator, int duration){
    this->title = title;
    this->description = description;
    this->status = status;
    this->creator = creator;
    this->duration = duration;
}
string Idea::getTitle() const{
    return title;
}
string Idea::getDescription() const{
    return description;
}
string Idea::getStatus() const{
    return status;
}
string Idea::getCreator() const{
    return creator;
}

int Idea::getDuration() const{
    return duration;
}

void Idea::accept(){
    this->status = "accepted";
}

void Idea::save() const{
    std::ofstream fout{this->getTitle() + ".txt"};
    fout << getTitle() << '\n' << getDescription() << '\n' << getStatus() << '\n' << getCreator() << '\n' << getDuration() << '\n' << std::flush;
    fout.close();
}

void Idea::setDescription(string str){
    this->description = str;
}
