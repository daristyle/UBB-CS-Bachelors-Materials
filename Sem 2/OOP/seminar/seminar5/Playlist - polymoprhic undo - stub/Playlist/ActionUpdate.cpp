#include "ActionUpdate.h"

ActionUpdate::ActionUpdate(Song oldSong, Song newSong, Repository& r): oldSong{oldSong}, newSong{newSong}, repo{r}{}

void ActionUpdate::executeUndo(){
    this->repo.removeSong(this->newSong);
    this->repo.addSong(this->oldSong);
}

void ActionUpdate::executeRedo(){
    this->repo.removeSong(this->oldSong);
    this->repo.addSong(this->newSong);
}