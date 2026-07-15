#include "Service.h"

#include <algorithm>
#include <fstream>
#include <stdexcept>

Service::Service(ResercherRepository& _researcherRepo, IdeaRepository& _ideaRepo): resercerRepo(_researcherRepo), ideaRepo(_ideaRepo){
}

vector<Idea> Service::getIdeas(){
    return ideaRepo.getIdeas();
}

vector<Researcher> Service::getResearchers(){
    return resercerRepo.getResearchers();
}

void Service::addIdea(string title, string description, string status, string creator, int duration){
    if(title == "") throw std::invalid_argument("Title cannot be empty");
    if(duration != 1 && duration != 2 && duration != 3) throw std::invalid_argument("Duration must be 1, 2 or 3");
    ideaRepo.addIdea(Idea(title, description, status, creator, duration));
}

void Service::acceptIdea(string title, string creator, int duration){
    ideaRepo.acceptIdea(Idea(title, "", "proposed", creator, duration));
}

bool Service::hasAcceptedIdeas(Researcher researcher){
    for(const auto& idea: getIdeas()){
        if(idea.getCreator() == researcher.getName() && idea.getStatus() == "accepted")
            return true;
    }
    return false;
}

void Service::saveAll(){
    auto v = getIdeas();
    std::sort(v.begin(), v.end(), [](const Idea& a, const Idea& b){
        return a.getDuration() < b.getDuration();
    });
    std::ofstream fout{"acceptedIdeas.txt"};
    for(auto idea: v){
        if(idea.getStatus() == "accepted"){
            fout<<idea.getTitle()<<'['<<idea.getCreator()<<"]-"<<idea.getDuration()<<" years-"<<idea.getDescription()<<'\n';
        }
    }
    fout<<std::flush;
}