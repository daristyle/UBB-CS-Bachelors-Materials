#include "Service.h"

#include <algorithm>
#include <iostream>
#include <ostream>

#include "CSVFileRepository.h"
#include "FileRepository.h"
#include "HTMLFileRepository.h"
#include "MemoryRepository.h"
#include "InterfaceRepository.h"
#include "TutorialValidator.h"

Service::Service(InterfaceRepository* _repository, InterfaceRepository* _watchlist): repo(_repository), watchlist(_watchlist) {
}

Service::~Service(){
    delete this->repo;
    delete this->watchlist;
}

void Service::addToRepo(const Tutorial& tutorial){
    TutorialValidator::validate(tutorial);
    this->repo->add(tutorial);
}

void Service::removeFromRepo(const Tutorial& tutorial){
    TutorialValidator::validate(tutorial);
    this->repo->remove(tutorial);
}

void Service::updateInRepo(const Tutorial& tutorial){
    TutorialValidator::validate(tutorial);
    this->repo->update(tutorial);
}

vector<Tutorial> Service::getAllFromRepo(){
    return this->repo->getAll();
}

vector<Tutorial> Service::getPresentedBy(const std::string& presenter){
    /*auto tutorials = this->repo.getAll();
    int i = 0;
    while(i<tutorials.size()){
        if(tutorials[i].get_presenter() != presenter){
            tutorials[i] = tutorials.back();
            tutorials.pop_back();
        }else{
            i++;
        }
    }
    return tutorials;*/
    auto tutorials = this->repo->getAll();
    vector<Tutorial> result;

    std::copy_if(tutorials.begin(), tutorials.end(), std::back_inserter(result),
        [presenter](const Tutorial& tutorial) -> bool{return tutorial.get_presenter() == presenter;});

    return result;
}

void Service::addToWatchlist(const Tutorial& tutorial){
    TutorialValidator::validate(tutorial);
    this->watchlist->add(tutorial);
}

void Service::removeFromWatchlist(const Tutorial& tutorial){
    TutorialValidator::validate(tutorial);
    this->watchlist->remove(tutorial);
}

vector<Tutorial> Service::getWatchlist(){
    return this->watchlist->getAll();
}

void Service::likeTutorial(const Tutorial& tutorial){
    TutorialValidator::validate(tutorial);
    this->repo->likeTutorial(tutorial);
}

void Service::switchToCSV(){
    delete this->watchlist;
    this->watchlist = new CSVFileRepository("tutorials.csv");
}

void Service::switchToHTML(){
    delete this->watchlist;
    this->watchlist = new HTMLFileRepository("tutorials.html");
}

void Service::openWatchlist(){
    this->watchlist->open();
}
