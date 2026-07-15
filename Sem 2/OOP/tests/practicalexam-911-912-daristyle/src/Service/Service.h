#pragma once

#include "src/Repository/ResercherRepository.h"
#include "src/Repository/IdeaRepository.h"

class Service {
private:
    ResercherRepository& resercerRepo;
    IdeaRepository& ideaRepo;

public:
    Service(ResercherRepository& resercherRepo, IdeaRepository& ideaRepo);
    vector<Researcher> getResearchers();
    vector<Idea> getIdeas();
    void acceptIdea(string title, string creator, int duration);
    void addIdea(string title, string description, string status, string creator, int duration);
    bool hasAcceptedIdeas(Researcher researcher);
    void saveAll();
};
