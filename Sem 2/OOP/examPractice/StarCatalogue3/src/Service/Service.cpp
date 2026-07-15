#include "Service.h"

Service::Service(AstronomerRepository& _astronomerRepository, StarRepository& _starRepository): astroRepo(_astronomerRepository), starRepo(_starRepository){
}

void Service::addStar(Star star){
    starRepo.addStar(star);
}

vector<Astronomer> Service::getAstronomers(){
    return astroRepo.getAstronomers();
}

vector<Star> Service::getStars(){
    return starRepo.getStars();
}

StarRepository& Service::getStarRepo(){
    return starRepo;
}