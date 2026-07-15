#pragma once

#include "Action.h"
#include "Repository.h"
#include "Song.h"

class ActionUpdate: public Action{
private:
    Song oldSong, newSong;
    Repository& repo;

public:
    ActionUpdate(Song oldSong, Song newSong, Repository& r);
    void executeUndo() override;
    void executeRedo() override;
    ~ActionUpdate() override = default;
};
