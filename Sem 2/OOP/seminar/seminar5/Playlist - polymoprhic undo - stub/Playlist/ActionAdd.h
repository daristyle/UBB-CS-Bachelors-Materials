#pragma once

#include "Action.h"
#include "Song.h"
#include "Repository.h"

class ActionAdd: public Action{
private:
    Song addedSong;
    Repository& repo;

public:
    ActionAdd(Song s, Repository& r);

    void executeUndo() override;
    void executeRedo() override;

    ~ActionAdd() override = default;
};