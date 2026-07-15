#include "Service.h"

Service::Service(){}

bool Service::addToRepo(const Tutorial& tutorial){
    return this->repo.add(tutorial);
}

bool Service::removeFromRepo(const Tutorial& tutorial){
    return this->repo.remove(tutorial);
}

bool Service::updateInRepo(const Tutorial& tutorial){
    return this->repo.update(tutorial);
}

vector<Tutorial> Service::getAllFromRepo(){
    return this->repo.getAll();
}

vector<Tutorial> Service::getPresentedBy(const std::string& presenter){
    auto tutorials = this->repo.getAll();
    int i = 0;
    while(i<tutorials.size()){
        if(tutorials[i].get_presenter() != presenter){
            tutorials[i] = tutorials.back();
            tutorials.pop_back();
        }else{
            i++;
        }
    }
    return tutorials;
}

bool Service::addToWatchlist(const Tutorial& tutorial){
    return this->watchlist.add(tutorial);
}

bool Service::removeFromWatchlist(const Tutorial& tutorial){
    return this->watchlist.remove(tutorial);
}

vector<Tutorial> Service::getWatchlist(){
    return this->watchlist.getAll();
}

void Service::likeTutorial(const Tutorial& tutorial){
    this->repo.likeTutorial(tutorial);
}