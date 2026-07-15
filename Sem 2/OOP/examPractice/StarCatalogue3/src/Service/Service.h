#pragma once
#include "AstronomerRepository.h"
#include "StarRepository.h"

class Service {
private:
    AstronomerRepository& astroRepo;
    StarRepository& starRepo;

public:
    Service(AstronomerRepository& astronomerRepository, StarRepository& starRepository);
    vector<Astronomer> getAstronomers();
    vector<Star> getStars();
    void addStar(Star star);
    StarRepository& getStarRepo();
};