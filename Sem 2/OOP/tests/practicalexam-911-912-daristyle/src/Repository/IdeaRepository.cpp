#include "IdeaRepository.h"
#include <fstream>
#include <sstream>
#include <filesystem>

void IdeaRepository::load(){
    std::ifstream fin{filename};
    string line, title, description, status, creator, durationStr;
    int duration;
    while(std::getline(fin, line)){
        std::stringstream ss{line};
        getline(ss, title, '|');
        getline(ss, description, '|');
        getline(ss, status, '|');
        getline(ss, creator, '|');
        getline(ss, durationStr);
        duration = std::stoi(durationStr);
        ideas.push_back(Idea(title, description, status, creator, duration));
    }
    fin.close();
}

void IdeaRepository::save(){
    for(const auto& idea : ideas){
        std::ofstream fout{idea.getTitle() + ".txt"};
        fout << idea.getTitle() << '\n' << idea.getDescription() << '\n' << idea.getStatus() << '\n' << idea.getCreator() << '\n' << idea.getDuration() << '\n' << std::flush;
        fout.close();
    }
}

IdeaRepository::IdeaRepository(string _filename): filename(_filename){
    if(!std::filesystem::exists(filename)){
        std::ofstream{filename}.close();
    }
    load();
}

void IdeaRepository::addIdea(Idea idea){
    ideas.push_back(idea);
}

vector<Idea> IdeaRepository::getIdeas(){
    return ideas;
}

void IdeaRepository::acceptIdea(Idea idea){
    for(auto& i : ideas){
        if(i.getTitle() == idea.getTitle() && i.getCreator() == idea.getCreator()){
            i.accept();
        }
    }
}

IdeaRepository::~IdeaRepository(){
    //save();
}
