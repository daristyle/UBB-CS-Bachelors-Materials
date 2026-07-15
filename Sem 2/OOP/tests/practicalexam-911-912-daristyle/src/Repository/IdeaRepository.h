#pragma once

#include "src/Domain/Idea.h"

#include <vector>
using std::vector;

class IdeaRepository {
private:
    vector<Idea> ideas;
    string filename;

    void load();
    void save();
public:
    IdeaRepository(string filename);
    vector<Idea> getIdeas();
    void addIdea(Idea idea);
    void acceptIdea(Idea idea);
    ~IdeaRepository();
};