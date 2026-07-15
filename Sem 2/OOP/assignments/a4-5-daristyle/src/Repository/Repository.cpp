#include "Repository.h"

Repository::Repository(bool hard_coded_elements){
    if(!hard_coded_elements){
        return;
    }
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
}

int Repository::find(const Tutorial& tutorial){
    for(int i = 0; i < this->tutorials.size(); i++){
        if(this->tutorials[i] == tutorial)
            return i;
    }
    return -1;
}

bool Repository::add(const Tutorial& tutorial){
    if(find(tutorial) == -1){
        this->tutorials.push_back(tutorial);
        return true;
    }
    return false;
}

bool Repository::remove(const Tutorial& tutorial){
    int pos = find(tutorial);
    if(pos != -1){
        this->tutorials[pos] = this->tutorials.back();
        this->tutorials.pop_back();
        return true;
    }
    return false;
}

bool Repository::update(const Tutorial& tutorial){
    int pos = find(tutorial);
    if(pos != -1){
        this->tutorials[pos] = tutorial;
        return true;
    }
    return false;
}

vector<Tutorial> Repository::getAll(){
    return this->tutorials;
}

void Repository::likeTutorial(const Tutorial& tutorial){
    auto pos = find(tutorial);
    if(pos != -1){
        this->tutorials[pos].like();
    }
}
